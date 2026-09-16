#include "../../include/utils/FileUtils.hpp"

#include <algorithm>
#include <stdexcept>

std::vector<std::filesystem::path>
FileUtils::discoverFiles(
    const std::filesystem::path& directory
) {

    if (!std::filesystem::exists(directory)) {
        throw std::runtime_error(
            "Directory does not exist: " +
            directory.string()
        );
    }

    if (!std::filesystem::is_directory(directory)) {
        throw std::runtime_error(
            "Path is not a directory: " +
            directory.string()
        );
    }

    std::vector<std::filesystem::path> files;

    for (
        const auto& entry :
        std::filesystem::recursive_directory_iterator(directory)
    ) {

        if (entry.is_regular_file()) {
            files.push_back(entry.path());
        }
    }

    std::sort(
        files.begin(),
        files.end()
    );

    return files;
}