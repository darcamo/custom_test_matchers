
find_package(Catch2 REQUIRED)

add_executable(test_custom_test_matchers
  main.cpp)
target_link_libraries(test_custom_test_matchers
  custom_test_matchers
  Catch2::Catch2WithMain)
