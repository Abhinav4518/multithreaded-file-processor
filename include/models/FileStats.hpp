#pragma once

#include <filesystem>
#include <cstddef>

struct FileStats {
    std::filesystem::path filePath;

    std::size_t lines = 0;
    std::size_t words = 0;
    std::size_t characters = 0;

    bool success = true;
};