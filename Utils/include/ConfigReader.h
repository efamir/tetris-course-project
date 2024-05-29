#ifndef COURSEWORK_CONFIGREADER_H
#define COURSEWORK_CONFIGREADER_H

#include <string>

namespace {
    enum ConfigOptions {
        BestScore, Difficulty, ColorScheme, FileDrawersNames
    };

    typedef unsigned int uint;
}

// singleton class
class ConfigReader {
    static ConfigReader * _instance;
protected:
    std::string _fileName;
    uint _bestScore;
    int _difficulty;
    int _colorScheme;
    bool validateAndUpdateData(ConfigOptions option, std::string const& value);

    ConfigReader(std::string const& fileName);
    ~ConfigReader();

public:
    // delete copy constructor and = operator
    ConfigReader(ConfigReader &obj) = delete;
    void operator=(ConfigReader const&) = delete;

    // called at the start of the program to initialise first instance
    static ConfigReader * getInstance(std::string const& fileName);

    // get initialised instance, if it's not throws runtime_error exception
    static ConfigReader * getInstance();

    // loads Config data from file and returns read params
    int loadConfigData();

    // saves config data to file
    bool saveConfigData();

    uint getBestScore();
    uint getDifficulty();
    uint getColorScheme();

    bool setBestScore(uint newBestScore);
    bool setDifficulty(uint difficulty);
    bool setColorScheme(uint cs);
};

#endif //COURSEWORK_CONFIGREADER_H