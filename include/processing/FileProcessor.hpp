#pragma once

#include "../models/FileStats.hpp"

#include <filesystem>

class FileProcessor {

public:

    static FileStats process(
        const std::filesystem::path& filePath
    );
};