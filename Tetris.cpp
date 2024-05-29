#include <iostream>
#include <getopt.h>

#include "Utils/include/ConfigReader.h"
#include "Utils/include/TetrisExecutor.h"
#include <chrono>
#include <thread>
#include "TetrisRenderer/include/CursorManipulations.h"

int convertIntToStr(std::string const& str) {
    constexpr int TOO_LARGE_NUMBER = -2;
    constexpr int INVALID_FORMAT = -1;
    constexpr int NEGATIVE_NUMBER = -3;

    try {
        size_t pos;
        int n = std::stoi(str, &pos);

        if (pos < str.size()) return INVALID_FORMAT;
        if (n < 0) return NEGATIVE_NUMBER;
        return n;
    } catch (std::invalid_argument const& e) {
        return INVALID_FORMAT;
    } catch (std::out_of_range const& e) {
        return TOO_LARGE_NUMBER;
    }
}

void print_usage() {
    std::cout << "Usage: tetris [options]\n";
    std::cout << " -d, --difficulty <arg>   Set the difficulty level\n";
    std::cout << " -c, --colorScheme <arg>  Set the color scheme\n";
    std::cout << " -r, --resetConfig        Reset the configuration\n";
    std::cout << " -b, --resetBestScore     Reset the best score\n";
    std::cout << " -h, --help               Display this help message\n";
}

int main(int argc, char* argv[]) {
    std::setlocale(LC_ALL, "");
    option options[] = {
            {"difficulty", required_argument, 0, 'd'},
            {"colorScheme", required_argument, 0, 'c'},
            {"resetConfig", no_argument, 0, 'r'},
            {"resetBestScore", no_argument, 0, 'b'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
    };
    int option;
    int optionIndex;

    const char * configFile = "config.txt";
    ConfigReader * configReader = ConfigReader::getInstance(configFile);

    int paramsRead = configReader->loadConfigData();

    bool breakFromLoop = false;
    while((option = getopt_long(argc, argv, "d:c:rbsh", options, &optionIndex)) != -1 && !breakFromLoop) {
        switch(option) {
            case 'h':
                print_usage();
                exit(0);
            case '?':
                print_usage();
                exit(-1);
            case 'd':
                configReader->setDifficulty(convertIntToStr(optarg));
                break;
            case 'c':
                configReader->setColorScheme(convertIntToStr(optarg));
                break;
            case 'r':
                configReader->setDifficulty(0);
                configReader->setColorScheme(0);
                configReader->setBestScore(0);
                configReader->saveConfigData();
                breakFromLoop = true;
                break;
            case 'b':
                configReader->setBestScore(0);
                break;
        }
    }

    constexpr int TARGET_PARAMS_READ = 3;
    constexpr int SECONDS_SHOWING_WARNING = 3;
    if (paramsRead == -1) {
        std::wcout << "Couldn't open config file. Continuing with passed/default params." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(SECONDS_SHOWING_WARNING));
        ANSIClearLine(std::wcout);
    } else if (paramsRead < TARGET_PARAMS_READ) {
        std::wcout << "Couldn't read " << TARGET_PARAMS_READ - paramsRead
                  << " params. Continuing with passed/default params." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(SECONDS_SHOWING_WARNING));
        ANSIClearLine(std::wcout);
    }

    TetrisExecutor tetrisExecutor;
    tetrisExecutor.initEverything();
    tetrisExecutor.runTetrisLoop();

    configReader->saveConfigData();

    return 0;
}
