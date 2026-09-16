#pragma once

#include "../models/FileStats.hpp"

#include <filesystem>
#include <vector>

class SequentialProcessor {

public:

    std::vector<FileStats> process(
        const std::vector<std::filesystem::path>& files
    );
};