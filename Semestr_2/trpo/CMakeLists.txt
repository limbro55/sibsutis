cmake_minimum_required(VERSION 3.20)
project(TypingTrainer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)

include_directories(include/)

add_executable(TypingTrainer src/main.cpp src/typing_trainer.cpp)

# Добавление Google Test через FetchContent
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# Распаковка и добавление Google Test к проекту
FetchContent_MakeAvailable(googletest)

enable_testing()

#Добавление тестов
add_executable(TestsTypingTrainer tests/test_typing_trainer.cpp src/typing_trainer.cpp)
target_link_libraries(TestsTypingTrainer GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(TestsTypingTrainer)