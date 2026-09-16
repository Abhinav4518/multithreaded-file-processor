#pragma once

#include "../models/FileStats.hpp"

#include <filesystem>
#include <cstddef>
#include <vector>

class ParallelProcessor {

public:

    explicit ParallelProcessor(
        std::size_t numberOfThreads
    );

    std::vector<FileStats> process(
        const std::vector<std::filesystem::path>& files
    );

private:

    std::size_t numberOfThreads_;
};