#include "../include/ConfigReader.h"
#include <fstream>
#include <unordered_map>

namespace {
    const std::string BEST_SCORE_STR = "bestScore";
    const std::string DIFFICULTY_STR = "difficulty";
    const std::string COLOR_SCHEME_STR = "colorScheme";

    constexpr char DELIM_CHAR = '=';

    const std::unordered_map<std::string, ConfigOptions> optionsStringMap = {
        {BEST_SCORE_STR, BestScore},
        {DIFFICULTY_STR, Difficulty},
        {COLOR_SCHEME_STR, ColorScheme},
    };

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

    constexpr uint DIFFICULTY_MIN = 1, DIFFICULTY_MAX = 5, CS_MIN = 0, CS_MAX = 10;
}

ConfigReader * ConfigReader::_instance = nullptr;

ConfigReader * ConfigReader::getInstance(const std::string &fileName) {
    if (_instance != nullptr) return _instance;
    _instance = new ConfigReader(fileName);
    return _instance;
}

ConfigReader * ConfigReader::getInstance() {
    if (_instance != nullptr) return _instance;
    throw std::runtime_error("Runtime error in ConfigReader::getInstance(): the instance hasn't been initialised yet.");
}

ConfigReader::ConfigReader(const std::string &fileName)
: _fileName(fileName), _bestScore(0), _difficulty(0), _colorScheme(0) {}

ConfigReader::~ConfigReader() {
    delete _instance;
}

int ConfigReader::loadConfigData() {
    std::ifstream file(_fileName);
    if (!file.is_open()) return -1;

    std::string key, value;

    int readParamsCount = 0;
    while ((file >> std::ws).good()) {
        if (!std::getline(file, key, DELIM_CHAR).good()) break;

        auto found = optionsStringMap.find(key);

        if (!std::getline(file, value)) break;

        size_t rI = value.find('\r');
        if (rI != value.npos) value.erase(rI);

        if (found != std::end(optionsStringMap) && validateAndUpdateData(found->second, value)) {
            readParamsCount++;
        }
    }

    return readParamsCount;
}

bool ConfigReader::validateAndUpdateData(ConfigOptions option, const std::string &value) {
    int tempN = convertIntToStr(value);
    if (tempN < 0) return false;
    uint n = static_cast<uint>(tempN);
    switch (option) {
        case BestScore:
            _bestScore = n;
            break;
        case Difficulty:
            if (n < DIFFICULTY_MIN || n > DIFFICULTY_MAX) return false;
            _difficulty = n;
            break;
        case ColorScheme:
            if (n < CS_MIN || n > CS_MAX) return false;
            _colorScheme = n;
            break;
        case FileDrawersNames:
            break;
    }

    return true;
}

uint ConfigReader::getBestScore() {return _bestScore;}

uint ConfigReader::getDifficulty() {return _difficulty;}

uint ConfigReader::getColorScheme() {return _colorScheme;}

bool ConfigReader::setBestScore(uint newBestScore) {
    _bestScore = newBestScore;
    return true;
}

bool ConfigReader::setDifficulty(uint difficulty) {
    if (difficulty < DIFFICULTY_MIN || difficulty > DIFFICULTY_MAX) return false;
    _difficulty = difficulty;
    return true;
}

bool ConfigReader::setColorScheme(uint cs) {
    if (cs < CS_MIN || cs > CS_MAX) return false;
    _colorScheme = cs;
    return true;
}

bool ConfigReader::saveConfigData() {
    std::ofstream file(_fileName);
    if (!file.is_open()) return false;

    file << BEST_SCORE_STR << DELIM_CHAR << _bestScore << '\n';
    if (!file.good()) return false;
    file << DIFFICULTY_STR << DELIM_CHAR << _difficulty << '\n';
    if (!file.good()) return false;
    file << COLOR_SCHEME_STR << DELIM_CHAR << _colorScheme << '\n';
    if (!file) return false;
    file.close();
    if (!file) return false;

    return true;
}
