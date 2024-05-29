#include "../include/TetrisGame.h"
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
    std::uniform_int_distribution<int> randFigure{0, TetrisInfo::NUM_OF_FIGURES};
    int newFigure = randFigure(Random::engine);
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
    for (int j = TetrisInfo::COL_TO_CHECK_FROM_ON_GAME_OVER; j < TetrisInfo::COL_TO_CHECK_TO_ON_GAME_OVER; j++) {
        if (field[TetrisInfo::ROW_TO_CHECK_ON_GAME_OVER][j] != Black)return true;
    }
    return false;
}

void TetrisGame::reDrawField() {
    for (int i = 0; i < FieldInfo::FIELD_ROWS; i++) {
        for (int j = 0; j < FieldInfo::FIELD_COLS; j++) {
            if (i < FieldInfo::ROW_COORDS_OFFSET)continue;
            tetrisRenderer.drawTetrisWindowBlock(i - FieldInfo::ROW_COORDS_OFFSET, j, field[i][j]);
        }
    }
}

void TetrisGame::checkOnFullRows() {
    std::vector<int> rowsIndex;

    while (inputReader.readNextChar() > 0) {}

    for (int i = 0; i < FieldInfo::FIELD_ROWS; i++) {
        bool isFull = true;
        for (int j = 0; j < FieldInfo::FIELD_COLS; j++) {
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
    double bonus = TetrisInfo::BONUS_POINTS_TO_ADD * rowsIndex.size() + TetrisInfo::BONUS_POINTS_TO_ADD * difficulty;
    score += (TetrisInfo::POINTS_TO_ADD + bonus) * rowsIndex.size();

    clearRow(rowsIndex);

    tetrisRenderer.setScore(score);
    tetrisRenderer.drawScore();
}

void TetrisGame::clearRow(std::vector<int> &rowsIndex) {
    int waitMls = TetrisInfo::CLEAR_ROW_DELAY - difficulty * TetrisInfo::CLEAR_ROW_DIFFICULTY_BOOST;

    //анімація мигання ряду перед зникненням
    for (int j = 0; j < 2; j++) {
        for (int i: rowsIndex) {
            for (int k = 0; k < FieldInfo::FIELD_COLS; k++) {
                if (i < FieldInfo::ROW_COORDS_OFFSET) { continue; }
                tetrisRenderer.drawTetrisWindowBlock(i - FieldInfo::ROW_COORDS_OFFSET, k, field[i][k], L'░');
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(waitMls));
        for (int i: rowsIndex) {
            for (int k = 0; k < FieldInfo::FIELD_COLS; k++) {
                if (i < FieldInfo::ROW_COORDS_OFFSET) { continue; }
                tetrisRenderer.drawTetrisWindowBlock(i - FieldInfo::ROW_COORDS_OFFSET, k, field[i][k]);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(waitMls));
    }
    //зникнення ряду
    for (int i: rowsIndex) {
        for (int j = 0; j < FieldInfo::FIELD_COLS; j++) {
            field[i][j] = Black;
            if (i < FieldInfo::ROW_COORDS_OFFSET) { continue; }
            tetrisRenderer.drawTetrisWindowBlock(i - FieldInfo::ROW_COORDS_OFFSET, j, field[i][j]);
        }
        moveBlocksDown(i);
    }
}

void TetrisGame::moveBlocksDown(int row) {
    for (int i = row; i > FieldInfo::ROW_COORDS_OFFSET; i--) {
        for (int j = 0; j < FieldInfo::FIELD_COLS; j++) {
            field[i][j] = field[i - 1][j];
            tetrisRenderer.drawTetrisWindowBlock(i - FieldInfo::ROW_COORDS_OFFSET, j, field[i][j]);
        }
    }

    for (int j = 0; j < FieldInfo::FIELD_COLS; j++) {
        field[0][j] = Black;
    }
}

GameFinishStatus TetrisGame::run() {
    double startDelay = TetrisInfo::defaultMinDelay + ((TetrisInfo::defaultMaxDelay - TetrisInfo::defaultMinDelay)
            / (TetrisInfo::NUM_OF_DIFFICULTY_LEVELS - 1)) * (TetrisInfo::NUM_OF_DIFFICULTY_LEVELS - difficulty);
    double diffCheck = startDelay;

    score = 0;
    tetrisRenderer.drawScore();
    char ch;
    bool flag = false;
    int gameFinish = -1;
    std::chrono::time_point<std::chrono::system_clock> start;
    ConfigReader *configReader = ConfigReader::getInstance();

    for (int i = 0; i < FieldInfo::FIELD_ROWS; ++i) {//очищаємо поле
        for (int j = 0; j < FieldInfo::FIELD_COLS; ++j) {
            field[i][j] = Black;
        }
    }

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
                processUserInput(ch, diffCheck, gameFinish);
            }

            fallDownOverTime(diffCheck, gameFinish, flag, start);

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

void TetrisGame::processUserInput(char ch, double &diffCheck, int &gameFinish) {
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
                    gameFinish = GameOver;
                }
                checkOnFullRows();
                putNextFigure();
                if (diffCheck >= TetrisInfo::defaultMinDelay) { diffCheck -= TetrisInfo::reduceTime; }
            }
            break;
        }
        case 'd':
            currentFigure->moveRight();
            break;
        case ' ':
            currentFigure->dropDown(score, difficulty);
            if (checkOnGameOver()) {
                tetrisRenderer.drawGameOver();
                gameFinish = GameOver;
            }
            checkOnFullRows();
            putNextFigure();
            break;
        case 'q':
            gameFinish = Exit;
            tetrisRenderer.drawGameOver();
            break;
        case 'r':
            gameFinish = Restart;
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
        if ((ch = inputReader.readNextChar()) > 0) {
            switch (ch) {
                case 'q':
                    gameFinish = Exit;

                    return;
                case 'r':
                    gameFinish = Restart;
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

void TetrisGame::fallDownOverTime(double &diffCheck, int &gameFinish, bool &flag,
                                  std::chrono::time_point<std::chrono::system_clock> start) {
    auto dif =
            std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now() - start).count();

    if (dif > diffCheck) {
        bool figureStoped = !currentFigure->moveDown();

        if (figureStoped) {
            if (checkOnGameOver()) {
                tetrisRenderer.drawGameOver();
                gameFinish = GameOver;
            }
            checkOnFullRows();
            putNextFigure();

            if (diffCheck >= TetrisInfo::defaultMinDelay) { diffCheck -= TetrisInfo::reduceTime; }
        }
        flag = !flag;
    }
}
