#pragma once

#include <filesystem>
#include <vector>

class FileUtils {

public:

    static std::vector<std::filesystem::path>
    discoverFiles(
        const std::filesystem::path& directory
    );
};