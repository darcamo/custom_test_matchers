

add_library(custom_test_matchers
  all.h
  all.cpp
  details/almost_equal_funcs.cpp
  details/almost_equal_funcs.h
  details/custom_string_makers.cpp
  details/custom_string_makers.h
  details/matchers_imp.cpp
  details/matchers_imp.h
  details/util.cpp
  details/util.h
  )
target_link_libraries(custom_test_matchers
  CONAN_PKG::catch2
  CONAN_PKG::armadillo
  CONAN_PKG::fmt
  )

target_include_directories(custom_test_matchers PUBLIC .)
