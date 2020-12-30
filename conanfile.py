import os
import shutil

from conans import CMake, ConanFile, tools


class CustomtestmatchersConan(ConanFile):
    name = "custom_test_matchers"
    version = "1.0.0"
    license = "GTEL Licence"
    author = "Darlan Cavalcante Moreira <darcamo@gmail.com>"
    url = "https://github.com/darcamo/conan-custom_test_matchers"
    description = "Custom catch2 test matchers for armadillo and other types."
    topics = ("C++", "catch", "tests")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    generators = "cmake"
    exports_sources = "CMakeLists.txt", "README.md", "src/*", "tests/*"

    def requirements(self):
        self.requires("Catch2/[>=2.11.0]@catchorg/stable")
        self.requires("fmt/[>=6.0.0]@bincrafters/stable")
        self.requires("armadillo/[>=10.1.2]@darcamo/stable")
        if self.options.shared:
            self.options["armadillo"].shared = True
        # self.options["armadillo"].use_extern_cxx11_rng = True
        # self.options["armadillo"].use_system_blas = True
        # self.options["armadillo"].use_system_hdf5 = True

    def build(self):
        cmake = CMake(self)
        os.mkdir("build")
        shutil.move("conanbuildinfo.cmake", "build/")
        cmake.configure(source_folder=".", build_folder="build")
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include/custom_test_matchers", src="src/")
        self.copy("*.a", dst="lib", src="build/lib/",keep_path=False)
        self.copy("*.so", dst="lib", src="build/lib/", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["custom_test_matchers"]
        self.cpp_info.includedirs.append("custom_test_matchers/fivegchannel")
