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
    int newFigure = randFigure(Random::engine); // generating random num to get random figure
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
            ptr = std::make_unique<Itetromino>(field, tetrisRenderer);
    }
    return ptr;
}

void TetrisGame::putNextFigure() {
    currentFigure = std::move(nextFigure); // replacing next figure as current
    nextFigure = generateNewFigure(); // generate next figure
    nextFigure->drawAsNextFigure(); // draw next figure as in next figure window
}

bool TetrisGame::checkOnGameOver() const {
    for (int j = TetrisInfo::COL_TO_CHECK_FROM_ON_GAME_OVER; j < TetrisInfo::COL_TO_CHECK_TO_ON_GAME_OVER; j++) {
        if (field[TetrisInfo::ROW_TO_CHECK_ON_GAME_OVER][j] != Black) { return true; }
    }
    return false;
}

void TetrisGame::reDrawField() const{
    for (int i = 0; i < FieldInfo::FIELD_ROWS; i++) {
        for (int j = 0; j < FieldInfo::FIELD_COLS; j++) {
            if (i < FieldInfo::ROW_COORDS_OFFSET)continue;
            tetrisRenderer.drawTetrisWindowBlock(i - FieldInfo::ROW_COORDS_OFFSET, j, field[i][j]);
        }
    }
}

void TetrisGame::checkOnFullRows() {
    std::vector<int> rowsIndex;

    while (inputReader.readNextChar() >
           0) {} // cleaning buffer to prevent reading unnecessary actions from being read during animation

    for (int i = 0; i < FieldInfo::FIELD_ROWS; i++) {
        bool isFull = true;
        for (int j = 0; j < FieldInfo::FIELD_COLS; j++) {
            if (field[i][j] == Black) { // if row consist at least 1 Black - it is not full
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

    clearRow(rowsIndex); // calling function of cleaning of full rows

    tetrisRenderer.setScore(score);
    tetrisRenderer.drawScore();
}

void TetrisGame::clearRow(std::vector<int> &rowsIndex) {
    blinkingRowsAnimation(rowsIndex);

    for (int i: rowsIndex) {
        for (int j = 0; j < FieldInfo::FIELD_COLS; j++) {
            field[i][j] = Black; // replacing coords with black
            if (i < FieldInfo::ROW_COORDS_OFFSET) { continue; }
            tetrisRenderer.drawTetrisWindowBlock(i - FieldInfo::ROW_COORDS_OFFSET, j, field[i][j]);
        }
        moveBlocksDown(i); // calling function to move all rows above down
    }
}

void TetrisGame::moveBlocksDown(int row) {
    //iterating from larger coords to the lower, because zero ones are on top and last ones are below
    for (int i = row; i > FieldInfo::ROW_COORDS_OFFSET; i--) {
        for (int j = 0; j < FieldInfo::FIELD_COLS; j++) {
            field[i][j] = field[i - 1][j];
            tetrisRenderer.drawTetrisWindowBlock(i - FieldInfo::ROW_COORDS_OFFSET, j, field[i][j]);
        }
    }
}

void TetrisGame::blinkingRowsAnimation(std::vector<int> rowsIndex) {
    int waitMls = TetrisInfo::CLEAR_ROW_DELAY - difficulty * TetrisInfo::CLEAR_ROW_DIFFICULTY_BOOST;

    for (int j = 0; j < TetrisInfo::NUM_OF_BLINKS; j++) {
        // drawing all full rows with shadow
        for (int i: rowsIndex) {
            for (int k = 0; k < FieldInfo::FIELD_COLS; k++) {
                if (i < FieldInfo::ROW_COORDS_OFFSET) { continue; }
                tetrisRenderer.drawTetrisWindowBlock(i - FieldInfo::ROW_COORDS_OFFSET, k, field[i][k], TetrisInfo::SHADOW_CHAR);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(waitMls));
        // drawing all full rows normally
        for (int i: rowsIndex) {
            for (int k = 0; k < FieldInfo::FIELD_COLS; k++) {
                if (i < FieldInfo::ROW_COORDS_OFFSET) { continue; }
                tetrisRenderer.drawTetrisWindowBlock(i - FieldInfo::ROW_COORDS_OFFSET, k, field[i][k]);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(waitMls));
    }
}

GameFinishStatus TetrisGame::run() {
    // calculating start delay based on difficulty
    double startDelay = TetrisInfo::DEFAULT_MIN_DELAY +
                        ((TetrisInfo::DEFAULT_MAX_DELAY - TetrisInfo::DEFAULT_MIN_DELAY)
                         / (TetrisInfo::NUM_OF_DIFFICULTY_LEVELS - 1)) *
                        (TetrisInfo::NUM_OF_DIFFICULTY_LEVELS - difficulty);

    double diffCheck = startDelay;

    score = 0;
    tetrisRenderer.setScore(score);
    tetrisRenderer.drawScore();
    char ch;
    bool flag = false;
    int gameFinish = -1; // for checking if game finished
    std::chrono::time_point<std::chrono::system_clock> start; // to track the time of automatic lowering of the figure
    ConfigReader *configReader = ConfigReader::getInstance();

    for (int i = 0; i < FieldInfo::FIELD_ROWS; ++i) { // clear the field
        for (int j = 0; j < FieldInfo::FIELD_COLS; ++j) {
            field[i][j] = Black;
        }
    }

    nextFigure = generateNewFigure(); // initializing next figure
    putNextFigure(); // set next figure as current and generate next one
    reDrawField();

    try {
        while (true) {

            if (!flag) {
                start = std::chrono::system_clock::now();
                flag = !flag;
            }

            if ((ch = inputReader.readNextChar()) > 0) { // if there is input - process it
                processUserInput(ch, diffCheck, gameFinish);
            }

            fallDownOverTime(diffCheck, gameFinish, flag, start); // if it is time - move figure down

            if (gameFinish >= 0) { // check if the game ended
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

    if (score > configReader->getBestScore()) { // if there is a new record - save new best score
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
            if (!figureStoped) { // if figure stopped - check on game over, check on full rows, put next figure, reduce delay
                if (checkOnGameOver()) {
                    tetrisRenderer.drawGameOver();
                    gameFinish = GameOver;
                }
                checkOnFullRows();
                putNextFigure();
                if (diffCheck >= TetrisInfo::DEFAULT_MIN_DELAY) { diffCheck -= TetrisInfo::REDUCE_DELAY; }
            }
            break;
        }
        case 'd':
            currentFigure->moveRight();
            break;
        case ' ':
            currentFigure->dropDown(score, difficulty);
            if (diffCheck >= TetrisInfo::DEFAULT_MIN_DELAY) { diffCheck -= TetrisInfo::REDUCE_DELAY; }
            if (checkOnGameOver()) { // figure stopped - check on game over, check on full rows, put next figure, reduce delay
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
                    std::chrono::system_clock::now() - start).count(); // calculate time from last drop

    if (dif > diffCheck) { // if it is right time - move figure down
        bool figureStoped = !currentFigure->moveDown();

        if (figureStoped) { // if figure stopped - check on game over, check on full rows, put next figure, reduce delay
            if (checkOnGameOver()) {
                tetrisRenderer.drawGameOver();
                gameFinish = GameOver;
            }
            checkOnFullRows();
            putNextFigure();

            if (diffCheck >= TetrisInfo::DEFAULT_MIN_DELAY) { diffCheck -= TetrisInfo::REDUCE_DELAY; }
        }
        flag = !flag;
    }
}
