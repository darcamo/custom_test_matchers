cmake_minimum_required(VERSION 3.15)
project(custom_test_matchers CXX)

add_library(custom_test_matchers)
target_sources(custom_test_matchers PUBLIC
  FILE_SET HEADERS
  BASE_DIRS include
  FILES
  include/custom_test_matchers/all.h
  include/custom_test_matchers/details/almost_equal_funcs.h
  include/custom_test_matchers/details/custom_string_makers.h
  include/custom_test_matchers/details/matchers_imp.h
  include/custom_test_matchers/details/util.h
)

target_sources(custom_test_matchers PRIVATE
  src/all.cpp
  src/details/almost_equal_funcs.cpp
  src/details/custom_string_makers.cpp
  src/details/matchers_imp.cpp
  src/details/util.cpp
)

find_package(Catch2 REQUIRED)
find_package(armadillo REQUIRED)
find_package(fmt REQUIRED)


target_link_libraries(custom_test_matchers PUBLIC
  Catch2::Catch2
  armadillo::armadillo
  fmt::fmt
)


install(TARGETS custom_test_matchers)
install(TARGETS custom_test_matchers FILE_SET HEADERS DESTINATION include)


add_subdirectory(tests)
