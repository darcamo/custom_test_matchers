cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(custom_test_matchers CONFIG REQUIRED)

add_executable(example src/example.cpp)
target_link_libraries(example custom_test_matchers::custom_test_matchers
)
