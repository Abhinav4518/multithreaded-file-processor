#include "../include/processing/ParallelProcessor.hpp"
#include "../include/processing/SequentialProcessor.hpp"
#include "../include/utils/Benchmark.hpp"
#include "../include/utils/FileUtils.hpp"

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <thread>

void printResults(
    const std::vector<FileStats>& results
) {

    std::size_t totalLines = 0;
    std::size_t totalWords = 0;
    std::size_t totalCharacters = 0;
    std::size_t failedFiles = 0;

    for (const auto& result : results) {

        totalLines += result.lines;
        totalWords += result.words;
        totalCharacters += result.characters;

        if (!result.success) {
            failedFiles++;
        }
    }

    std::cout << "\nResults\n";
    std::cout << "--------------------------------\n";

    std::cout
        << "Files processed : "
        << results.size()
        << '\n';

    std::cout
        << "Failed files    : "
        << failedFiles
        << '\n';

    std::cout
        << "Total lines     : "
        << totalLines
        << '\n';

    std::cout
        << "Total words     : "
        << totalWords
        << '\n';

    std::cout
        << "Total characters: "
        << totalCharacters
        << '\n';
}

int main(int argc, char* argv[]) {

    if (argc < 2) {

        std::cerr
            << "Usage: "
            << argv[0]
            << " <directory> [threads]\n";

        return EXIT_FAILURE;
    }

    std::string directory = argv[1];

    std::size_t threads =
        argc >= 3
            ? std::stoull(argv[2])
            : std::thread::hardware_concurrency();

    if (threads == 0) {
        threads = 2;
    }

    try {

        std::cout
            << "========================================\n";

        std::cout
            << " MultiThreaded File Processing Engine\n";

        std::cout
            << "========================================\n\n";

        std::cout
            << "Input directory : "
            << directory
            << '\n';

        std::cout
            << "Worker threads   : "
            << threads
            << "\n\n";

        auto files =
            FileUtils::discoverFiles(directory);

        if (files.empty()) {

            std::cout
                << "No files found.\n";

            return EXIT_SUCCESS;
        }

        std::cout
            << "Files discovered : "
            << files.size()
            << "\n";

        // -----------------------------------
        // Sequential benchmark
        // -----------------------------------

        SequentialProcessor sequential;

        auto [sequentialResults, sequentialTime] =
            Benchmark::measure(
                [&]() {
                    return sequential.process(files);
                }
            );

        // -----------------------------------
        // Parallel benchmark
        // -----------------------------------

        ParallelProcessor parallel(threads);

        auto [parallelResults, parallelTime] =
            Benchmark::measure(
                [&]() {
                    return parallel.process(files);
                }
            );

        // -----------------------------------
        // Output
        // -----------------------------------

        printResults(parallelResults);

        std::cout
            << "\nPerformance\n";

        std::cout
            << "--------------------------------\n";

        std::cout
            << std::fixed
            << std::setprecision(2);

        std::cout
            << "Sequential time : "
            << sequentialTime
            << " ms\n";

        std::cout
            << "Parallel time   : "
            << parallelTime
            << " ms\n";

        if (parallelTime > 0) {

            double speedup =
                sequentialTime / parallelTime;

            std::cout
                << "Speedup         : "
                << speedup
                << "x\n";
        }

        std::cout
            << "\n";

        return EXIT_SUCCESS;
    }
    catch (const std::exception& exception) {

        std::cerr
            << "Error: "
            << exception.what()
            << '\n';

        return EXIT_FAILURE;
    }
}