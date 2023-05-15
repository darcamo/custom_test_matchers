# noqa: D100

from conan import ConanFile
from conan.tools.cmake import CMakeToolchain, CMake, cmake_layout, CMakeDeps


class custom_test_matchersRecipe(ConanFile):    # noqa: D101
    name = "custom_test_matchers"
    version = "2.0"

    # Optional metadata
    license = "GTEL Licence"
    author = "Darlan Cavalcante Moreira <darcamo@gmail.com>"
    url = "https://github.com/darcamo/conan-custom_test_matchers"
    description = "Custom catch2 test matchers for armadillo and other types."
    topics = ("C++", "catch", "tests")

    # Binary configuration
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}

    # Sources are located in the same place as this recipe, copy them
    # to the recipe
    exports_sources = "CMakeLists.txt", "include/*", "src/*", "tests/*"

    def requirements(self):    # noqa: D102
        self.requires("catch2/[>=3.3.2]", transitive_headers=True)
        self.requires("fmt/[>=9.1.0]")
        self.requires("armadillo/[>=12.0.1]@gtel/stable",
                      transitive_headers=True)

    def config_options(self):    # noqa: D102
        if self.settings.os == "Windows":
            self.options.rm_safe("fPIC")

    def configure(self):    # noqa: D102
        if self.options.shared:
            self.options.rm_safe("fPIC")

    def layout(self):    # noqa: D102
        cmake_layout(self)

    def generate(self):    # noqa: D102
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build(self):    # noqa: D102
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):    # noqa: D102
        cmake = CMake(self)
        cmake.install()

    def package_info(self):    # noqa: D102
        self.cpp_info.libs = ["custom_test_matchers"]
