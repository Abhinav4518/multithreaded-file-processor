#include "../include/processing/FileProcessor.hpp"

#include <cassert>
#include <filesystem>
#include <fstream>
#include <iostream>

int main() {

    std::filesystem::path testFile =
        "test_input.txt";

    {
        std::ofstream file(testFile);

        file << "Hello world\n";
        file << "C++ multithreading\n";
    }

    FileStats result =
        FileProcessor::process(testFile);

    assert(result.success);
    assert(result.lines == 2);
    assert(result.words == 4);

    std::filesystem::remove(testFile);

    std::cout
        << "All tests passed!\n";

    return 0;
}