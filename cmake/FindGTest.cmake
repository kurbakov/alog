include(FetchContent)

set(googletest_BUILD_TESTS OFF)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest
        GIT_TAG v1.12.0
)

FetchContent_MakeAvailable(googletest)
