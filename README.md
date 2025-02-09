# ::alog

Asynchronous logger designed with latency in mind

## About

This is a hobby project implementation of the asynchronous logger in C++. The library is focusing on 2 following items:
1. Make sure we minimise the workload on the `hot path`. The thread that issues the log should have the minimal cost of log issuing.
2. It should be easy to provide the custom output stream. Most of the logging libraries rely on logging to stdout or file. This library is created with the goal to simplify the adding of the custom logging destination.

## How to use

`::alog` is a classic CMake project and can be easily integrated in any other CMake project with [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html) functionality.

Here is an example how you can do it. In your [CMakeLists.txt](./test/integr/CMakeLists.txt) file add:

```cmake
include(FetchContent)

# Configure the libary based on your needs
set(ALOG_LEVEL ::alog::Level::INFO)

FetchContent_Declare(alog
    GIT_REPOSITORY https://github.com/kurbakov/alog
    GIT_TAG origin/main
)
FetchContent_MakeAvailable(alog)
```

Full list of `::alog` config parameters can be found in [configs](./cmake/ConfigParams.cmake)

And make sure you link your main against the alog library:

```cmake
add_executable(main main.cpp)
target_link_libraries(main PRIVATE alog)
```

In the [main.cpp](./test/integr/main.cpp)

```cpp
#include <alog/Logger.hpp>

int main () {
    // make sure to initialise the logger and define the Out stream
    alog::initLogger<alog::Stream::IO>();

    // issue a log to the given Out stream
    LOG_INFO("Simple INFO log to stdout");
    LOG_INFO("Simple INFO log to stdout with arg: {}", 10);

    return 0;
}
```

And to [build](./test/integr/build.sh)

```bash
mkdir build && cd build
cmake ..
make -j4
./main
```

That is it!

## Contribute

Fork the project, add a change and create the PR.

Please make sure you run the checks before submitting the change. just execute [build-report.sh](./scripts/build-report.sh).
