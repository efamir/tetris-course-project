#include <iostream>
#include <getopt.h>

#include "Utils/include/ConfigReader.h"
#include "Utils/include/TetrisExecutor.h"
#include <chrono>
#include <thread>
#include "TetrisRenderer/include/CursorManipulations.h"

namespace {
    const std::string FILE_NAME = "config.txt";
}

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

// print option list
void print_usage() {
    std::cout << "Usage: tetris [options]\n";
    std::cout << " -d, --difficulty <arg>   Set the difficulty level\n";
    std::cout << " -c, --colorScheme <arg>  Set the color scheme\n";
    std::cout << " -r, --resetConfig        Reset the configuration\n";
    std::cout << " -b, --resetBestScore     Reset the best score\n";
    std::cout << " -h, --help               Display this help message\n";
}

int main(int argc, char* argv[]) {
    // sets locate for wcout stream
    std::setlocale(LC_ALL, "");


    const option options[] = {
            {"difficulty", required_argument, 0, 'd'},
            {"colorScheme", required_argument, 0, 'c'},
            {"resetConfig", no_argument, 0, 'r'},
            {"resetBestScore", no_argument, 0, 'b'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
    };
    int option;
    int optionIndex; // unused variable

    ConfigReader * configReader = ConfigReader::getInstance(FILE_NAME);

    int paramsRead = configReader->loadConfigData();

    bool breakFromLoop = false;
    while((option = getopt_long(argc, argv, "d:c:rbsh", options, &optionIndex)) != -1 && !breakFromLoop) {
        switch(option) {
            case 'h':
                print_usage();
                exit(0);
            case '?':
                print_usage();
                exit(-1); // if wrong options exit with -1 status
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

        // sleep to let user read the warning message
        std::this_thread::sleep_for(std::chrono::seconds(SECONDS_SHOWING_WARNING));

        ANSIClearLine(std::wcout); // clear warning message line
    } else if (paramsRead < TARGET_PARAMS_READ) {
        std::wcout << "Couldn't read " << TARGET_PARAMS_READ - paramsRead
                  << " params. Continuing with passed/default params." << std::flush;

        // sleep to let user read the warning message
        std::this_thread::sleep_for(std::chrono::seconds(SECONDS_SHOWING_WARNING));

        ANSIClearLine(std::wcout); // clear warning message line
    }

    try {
        TetrisExecutor tetrisExecutor;
        tetrisExecutor.initEverything();
        tetrisExecutor.runTetrisLoop();
    } catch (std::out_of_range const& e) {
        std::wcerr << ColorANSI::get(Error) << e.what() << '\n';
        return EXIT_FAILURE;
    } catch (std::runtime_error const& e) {
        std::wcerr << ColorANSI::get(Error) << e.what() << '\n';
        return EXIT_FAILURE;
    } catch (...) {
        std::wcerr << ColorANSI::get(Error) << "Unexpected error was caught in main() function." << '\n';
        return EXIT_FAILURE;
    }

    configReader->saveConfigData();

    return EXIT_SUCCESS;
}
