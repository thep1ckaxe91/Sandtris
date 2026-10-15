from conan import ConanFile
from conan.tools.cmake import cmake_layout

class SandtrisConan(ConanFile):
    name = "Sandtris"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    
    requires = [
            "protobuf/6.32.1",
            "gtest/1.17.0",
            "sdl/2.32.10",
            "sdl_ttf/2.24.0",
            "sdl_image/2.8.8",
            "sdl_mixer/2.8.1",
            "libsdlgame/0.1.0"
        ]

    default_options = {
        "sdl/*:wayland": False,
        "sdl/*:pulse": False,
    }

    def requirements(self):
        pass

    def configure(self):
        pass

    def layout(self):
        cmake_layout(self)

    def generate(self):
        from conan.tools.cmake import CMakeDeps, CMakeToolchain
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

    def build_requirements(self):
        self.tool_requires("m4/1.4.19")
