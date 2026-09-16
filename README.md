# MultiThreaded File Processing Engine

A modular C++17 application that compares sequential and concurrent
file processing using a custom thread pool.

## Features

- Sequential file processing
- Multithreaded file processing
- Custom thread pool
- Thread-safe task queue
- Producer-consumer architecture
- Mutex-based synchronization
- Condition variables
- Atomic state management
- Futures for task results
- Graceful worker shutdown
- Performance benchmarking
- CMake build system

## Architecture

```text
File Discovery
      |
      v
Task Queue
      |
      v
Thread Pool
  /   |   \
 T1   T2   T3
  \   |   /
   Results
      |
      v
Benchmark