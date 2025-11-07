cmake_minimum_required(VERSION 3.16)
project(lab4_oop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB SRC_FILES src/*.cpp)

add_executable(lab4_oop
    ${SRC_FILES}
)

include(FetchContent)
cmake_policy(SET CMP0135 NEW)  

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

file(GLOB TEST_FILES tests/*.cpp)

add_executable(lab4_oop_tests
    ${TEST_FILES}
)

target_link_libraries(lab4_oop_tests
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lab4_oop_tests)

