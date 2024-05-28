#include "../include/TetrisGame.h"
//#include "../include/Figures/TetrisBaseFigure.h"
#include "../include/Figures/Itetromino.h"
#include "../include/Figures/Jtetromino.h"
#include "../include/Figures/Ltetromino.h"
#include "../include/Figures/Otetromino.h"
#include "../include/Figures/Stetromino.h"
#include "../include/Figures/Ztetromino.h"
#include "../include/Figures/Ttetromino.h"
#include "../../Utils/include/ConfigReader.h"

TetrisGame::TetrisGame(TetrisRenderer &tetrisRenderer, InputReader &inputReader) : tetrisRenderer(tetrisRenderer),
                                                                                   inputReader(inputReader) {
    score = 0;
    ConfigReader *configReader = ConfigReader::getInstance();
    difficulty = configReader->getDifficulty();
}

std::unique_ptr<Figure> TetrisGame::generateNewFigure() {
    std::uniform_int_distribution<int> randFigure{0, 6};
    int newFigure = randFigure(engine);
    std::unique_ptr<Figure> ptr;
    switch (newFigure) {
        case 0:
            ptr = std::make_unique<Itetromino>(field, tetrisRenderer);
            break;
        case 1:
            ptr = std::make_unique<Jtetromino>(field, tetrisRenderer);
            break;
        case 2:
            ptr = std::make_unique<Ttetromino>(field, tetrisRenderer);
            break;
        case 3:
            ptr = std::make_unique<Ltetromino>(field, tetrisRenderer);
            break;
        case 4:
            ptr = std::make_unique<Stetromino>(field, tetrisRenderer);
            break;
        case 5:
            ptr = std::make_unique<Ztetromino>(field, tetrisRenderer);
            break;
        case 6:
            ptr = std::make_unique<Otetromino>(field, tetrisRenderer);
            break;
        default:
            throw std::runtime_error("Wrong num of generated figure");
    }
    return ptr;
}

void TetrisGame::putNextFigure() {
    currentFigure = std::move(nextFigure);
    nextFigure = generateNewFigure();
    nextFigure->drawAsNextFigure();

}

bool TetrisGame::checkOnGameOver() {
    for (int j = 3; j < 7; j++) {
        if (field[2][j] != Black)return true;
    }
    return false;
}

void TetrisGame::reDrawField() {
    for (int i = 0; i < 22; i++) {
        for (int j = 0; j < 10; j++) {
            if (i <= 1)continue;
            tetrisRenderer.drawTetrisWindowBlock(i - 2, j, field[i][j]);
        }
    }
}

void TetrisGame::checkOnFullRows() {
    std::vector<int> rowsIndex;

    while (inputReader.readNextChar() > 0) {}

    for (int i = 0; i < 22; i++) {
        bool isFull = true;
        for (int j = 0; j < 10; j++) {
            if (field[i][j] == Black) {
                isFull = false;
                break;
            }
        }
        if (isFull) {
            rowsIndex.push_back(i);
        }
    }

    if (rowsIndex.empty()) { return; }
    double bonus = 100 * rowsIndex.size() + 100 * difficulty;
    score += (1000 + bonus) * rowsIndex.size();

    clearRow(rowsIndex);

    tetrisRenderer.setScore(score);
    tetrisRenderer.drawScore();
}

void TetrisGame::clearRow(std::vector<int> &rowsIndex) {
    int waitMls = 125 - difficulty*10;

    for (int j = 0; j < 2; j++) {
        for (int i: rowsIndex) {
            for (int k = 0; k < 10; k++) {
                if (i <= 1) { continue; }
                tetrisRenderer.drawTetrisWindowBlock(i - 2, k, field[i][k],L'░');
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(waitMls));
        for (int i: rowsIndex) {
            for (int k = 0; k < 10; k++) {
                if (i <= 1) { continue; }
                tetrisRenderer.drawTetrisWindowBlock(i - 2, k, field[i][k]);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(waitMls));
    }

    for (int i: rowsIndex) {
        for (int j = 0; j < 10; j++) {
            field[i][j] = Black;
            if (i <= 1) { continue; }
            tetrisRenderer.drawTetrisWindowBlock(i - 2, j, field[i][j]);
        }
        moveBlocksDown(i);
    }
}

void TetrisGame::moveBlocksDown(int row) {
    for (int i = row; i >
                      2; i--) {
        for (int j = 0; j < 10; j++) {
            field[i][j] = field[i - 1][j];
            tetrisRenderer.drawTetrisWindowBlock(i - 2, j, field[i][j]);
        }
    }

    for (int j = 0; j < 10; j++) {
        field[0][j] = Black;
    }
}

GameFinishStatus TetrisGame::run() {
    double defaultMaxDelay = 500;//500
    double defaultMinDelay = 100;//100
    double reduceTime = 1;//10

    double startDelay = defaultMinDelay + ((defaultMaxDelay - defaultMinDelay) / (5 - 1)) * (5 - difficulty);
    double diffCheck = startDelay;

    score = 0;
    char ch;
    bool flag = false;
    int gameFinish = -1;
    std::chrono::time_point<std::chrono::system_clock> start;
    ConfigReader *configReader = ConfigReader::getInstance();

    for (int i = 0; i < 22; ++i)
        for (int j = 0; j < 10; ++j)
            field[i][j] = Black;
    nextFigure = generateNewFigure();//ініціалізуємо наступну фігуру
    putNextFigure();//робимо наступну фігуру теперішньою фігурою і генеруємо нову наступну фігуру
    reDrawField();

    try {
        while (true) {

            if (!flag) {
                start = std::chrono::system_clock::now();
                flag = !flag;
            }

            if ((ch = inputReader.readNextChar()) > 0) {
                processUserInput(ch, diffCheck, gameFinish, defaultMinDelay, reduceTime);
            }

            fallDawnOverTime(diffCheck, gameFinish, flag, start, defaultMinDelay, reduceTime);

            if (gameFinish >= 0) {
                if (score > configReader->getBestScore()) {
                    configReader->setBestScore(score);
                }
                return static_cast<GameFinishStatus>(gameFinish);
            }

        }
    } catch (std::runtime_error const &e) {
        inputReader.resetFlags();
        std::cerr << "\n" << e.what() << "\n";
    } catch (...) {
        inputReader.resetFlags();
    }

    if (score > configReader->getBestScore()) {
        configReader->setBestScore(score);
    }
    return GameFinishStatus::GameOver;
}

void TetrisGame::processUserInput(char ch, double &diffCheck, int &gameFinish, double minTime, double reduceTime) {
    switch (ch) {
        case 'w':
            currentFigure->rotate();
            break;
        case 'a':
            currentFigure->moveLeft();
            break;
        case 's': {
            bool figureStoped = currentFigure->moveDown();
            if (!figureStoped) {
                if (checkOnGameOver()) {
                    tetrisRenderer.drawGameOver();
                    gameFinish = 2;
                }
                checkOnFullRows();
                putNextFigure();
                if (diffCheck >= minTime) { diffCheck -= reduceTime; }
            }
            break;
        }
        case 'd':
            currentFigure->moveRight();
            break;
        case ' ':
            currentFigure->dropDown(score,difficulty);
            checkOnFullRows();
            putNextFigure();
            break;
        case 'q':
            gameFinish = 0;
            tetrisRenderer.drawGameOver();
            break;
        case 'r':
            gameFinish = 1;
            break;
        case 'p':
            gamePause(gameFinish);
            break;
        default:
            break;
    }
}

void TetrisGame::gamePause(int &gameFinish) {
    tetrisRenderer.drawPause();
    char ch;

    while (true) {
        if ((ch = inputReader.readNextChar()) > 0) { // HERE
            switch (ch) {
                case 'q':
                    gameFinish = 0;

                    return;
                case 'r':
                    gameFinish = 1;
                    return;
                case 'p':
                    reDrawField();
                    return;
                default:
                    break;
            }
        }
    }
}

void TetrisGame::fallDawnOverTime(double &diffCheck, int &gameFinish, bool &flag,
                                  std::chrono::time_point<std::chrono::system_clock> start, double minTime,
                                  double reduceTime) {
    auto dif =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now() - start).count();

    if (dif > diffCheck) {
        bool figureStoped = currentFigure->moveDown();

        if (!figureStoped) {

            if (checkOnGameOver()) {
                tetrisRenderer.drawGameOver();
                gameFinish = 2;
            }

            checkOnFullRows();
            putNextFigure();

            if (diffCheck >= minTime) { diffCheck -= reduceTime; }
        }

        flag = !flag;
    }
}
