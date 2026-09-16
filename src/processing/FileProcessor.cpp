#include "../../include/processing/FileProcessor.hpp"

#include <fstream>
#include <sstream>
#include <string>

FileStats FileProcessor::process(
    const std::filesystem::path& filePath
) {

    FileStats result;

    result.filePath = filePath;

    std::ifstream file(filePath);

    if (!file.is_open()) {
        result.success = false;
        return result;
    }

    std::string line;

    while (std::getline(file, line)) {

        result.lines++;

        result.characters += line.size();

        std::istringstream stream(line);

        std::string word;

        while (stream >> word) {
            result.words++;
        }
    }

    return result;
}