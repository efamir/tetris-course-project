#ifndef COURSEWORK_CONFIGREADER_H
#define COURSEWORK_CONFIGREADER_H

#include <string>

namespace {
    enum ConfigOptions {
        BestScore, Difficulty, ColorScheme, FileDrawersNames
    };

    typedef unsigned int uint;
}

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
    ConfigReader(ConfigReader &obj) = delete;
    void operator=(ConfigReader const&) = delete;

    static ConfigReader * getInstance(std::string const& fileName);
    static ConfigReader * getInstance();

    int loadConfigData();
    bool saveConfigData();

    uint getBestScore();
    uint getDifficulty();
    uint getColorScheme();

    bool setBestScore(uint newBestScore);
    bool setDifficulty(uint difficulty);
    bool setColorScheme(uint cs);
};

#endif //COURSEWORK_CONFIGREADER_H