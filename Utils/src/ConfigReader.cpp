#include "../include/ConfigReader.h"
#include <fstream>
#include <unordered_map>

namespace {

std::unordered_map<std::string, ConfigOptions> optionsStringMap = {
    {"bestScore", BestScore},
    {"difficulty", Difficulty},
    {"colorScheme", ColorScheme},
};

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
    struct ParamLimits {
        ParamLimits(uint dMin = 0, uint dMax = 5, uint csMin_ = 0, uint csMax_ = 5)
                : difficultyMin(dMin), difficultyMax(dMax), csMin(csMin_), csMax(csMax_) {}
        const uint difficultyMin, difficultyMax, csMin, csMax;
    };

    ParamLimits defaultParams(0, 5, 0, 5); // todo change later
}

ConfigReader * ConfigReader::_instance = nullptr;

ConfigReader * ConfigReader::getInstance(const std::string &fileName) {
    if (_instance != nullptr) return _instance;
    _instance = new ConfigReader(fileName);
    return _instance;
}

ConfigReader * ConfigReader::getInstance() {
    if (_instance != nullptr) return _instance;
    // todo What if not created?
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
        if (!std::getline(file, key, '=').good()) break;

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
            if (n < defaultParams.difficultyMin || n > defaultParams.difficultyMax) return false;
            _difficulty = n;
            break;
        case ColorScheme:
            if (n < defaultParams.csMin || n > defaultParams.csMax) return false;
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
    if (difficulty < defaultParams.difficultyMin || difficulty > defaultParams.difficultyMax) return false;
    _difficulty = difficulty;
    return true;
}

bool ConfigReader::setColorScheme(uint cs) {
    if (cs < defaultParams.csMin || cs > defaultParams.csMax) return false;
    _colorScheme = cs;
    return true;
}

bool ConfigReader::saveConfigData() {
    std::ofstream file(_fileName);
    if (!file.is_open()) return false;

    file << "bestScore=" << _bestScore << "\n"; // todo remove hardcode
    if (!file.good()) return false;
    file << "difficulty=" << _difficulty << "\n";
    if (!file.good()) return false;
    file << "colorScheme=" << _colorScheme << "\n";
    if (!file) return false;
    file.close();
    if (!file) return false;

    return true;
}
