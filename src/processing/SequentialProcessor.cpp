#include "../../include/processing/SequentialProcessor.hpp"

#include "../../include/processing/FileProcessor.hpp"

std::vector<FileStats>
SequentialProcessor::process(
    const std::vector<std::filesystem::path>& files
) {

    std::vector<FileStats> results;

    results.reserve(files.size());

    for (const auto& file : files) {

        results.push_back(
            FileProcessor::process(file)
        );
    }

    return results;
}