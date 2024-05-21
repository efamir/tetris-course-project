#include <iostream>
#include <getopt.h>

#include "Utils/include/ConfigReader.h"
// #include "Utils/include/TetrisExecutor.h"
#include <chrono>
#include <thread>

int convertIntToStr(std::string const& str) {
    try {
        size_t pos;
        int n = std::stoi(str, &pos);

        if (pos < str.size()) return -1;
        if (n < 0) return -2;
        return n;
    } catch (std::invalid_argument const& e) {
        return -1;
    } catch (std::out_of_range const& e) {
        return -2;
    }
}

void print_usage() {
    std::cout << "Usage: tetris [options]\n";
    std::cout << " -d, --difficulty <arg>   Set the difficulty level\n";
    std::cout << " -c, --colorScheme <arg>  Set the color scheme\n";
    std::cout << " -r, --resetConfig        Reset the configuration\n";
    std::cout << " -b, --resetBestScore     Reset the best score\n";
    std::cout << " -s, --saveConfig         Save the configuration\n";
    std::cout << " -h, --help               Display this help message\n";
}

int main(int argc, char* argv[]) {
    option options[] = {
            {"difficulty", required_argument, 0, 'd'},
            {"colorScheme", required_argument, 0, 'c'},
            {"resetConfig", no_argument, 0, 'r'},
            {"resetBestScore", no_argument, 0, 'b'},
            {"saveConfig", no_argument, 0, 's'},
            {"help", no_argument, 0, 'h'},
            {0, 0, 0, 0}
    };
    int option;
    int optionIndex;
    bool saveConfigChanges = false;

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
            case 's':
                saveConfigChanges = true;
                break;
        }
    }

    int targetParamsRead = 3;
    int secondShowingInfo = 3;
    if (paramsRead == -1) {
        std::cout << "Couldn't open config file. Continuing with passed/default params." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(secondShowingInfo));
        std::cout << "\r";
        for (int _ = 0; _ < 75; ++_) std::cout << ' '; // todo find better way to clean
        std::cout << "\r";
    } else if (paramsRead < targetParamsRead) {
        std::cout << "Couldn't read " << targetParamsRead - paramsRead
                  << "params. Continuing with passed/default params." << std::flush;
        std::this_thread::sleep_for(std::chrono::seconds(secondShowingInfo));
        std::cout << "\r";
        for (int _ = 0; _ < 75; ++_) std::cout << ' ';
        std::cout << "\r";
    }

    if (saveConfigChanges) configReader->saveConfigData();

    std::cout << "Best score: " << configReader->getBestScore() << "\n";
    std::cout << "Cs: " <<  configReader->getColorScheme() << "\n";
    std::cout << "Difficulty: " << configReader->getDifficulty() << "\n";
//     TetrisExecutor tetrisExecutor;
//     tetrisExecutor.runTetrisLoop();

    return 0;
}
