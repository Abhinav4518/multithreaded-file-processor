#include "../../include/processing/ParallelProcessor.hpp"

#include "../../include/core/ThreadPool.hpp"
#include "../../include/processing/FileProcessor.hpp"

#include <future>

ParallelProcessor::ParallelProcessor(
    std::size_t numberOfThreads
)
    : numberOfThreads_(numberOfThreads)
{
}

std::vector<FileStats>
ParallelProcessor::process(
    const std::vector<std::filesystem::path>& files
) {

    ThreadPool pool(numberOfThreads_);

    std::vector<
        std::future<FileStats>
    > futures;

    futures.reserve(files.size());

    for (const auto& file : files) {

        futures.push_back(
            pool.submit(
                FileProcessor::process,
                file
            )
        );
    }

    std::vector<FileStats> results;

    results.reserve(files.size());

    for (auto& future : futures) {

        results.push_back(
            future.get()
        );
    }

    pool.shutdown();

    return results;
}