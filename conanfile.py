from conan import ConanFile
from conan.tools.cmake import cmake_layout

class MyProjectConan(ConanFile):
    name = "my_project"
    version = "1.0"
    settings = "os", "compiler", "build_type", "arch"
    
    requires = [
            "protobuf/6.32.1",
            "gtest/1.17.0",
            "sdl/2.32.10",
            "sdl_ttf/2.24.0",
            "sdl_image/2.8.8",
            "sdl_mixer/2.8.1"
        ]

    default_options = {
        "sdl/*:wayland": False,
        "pulseaudio/*:shared": True
    }

    def requirements(self):
        pass

    def configure(self):
        pass

    def layout(self):
        cmake_layout(self)

    def generate(self):
        compat_flags_c = [
            "-Wno-error=implicit-function-declaration",
            "-Wno-error=int-conversion",
            "-Wno-error=attributes",
            "-std=gnu17"
        ]
        compat_flags_cxx = [
            "-Wno-error=implicit-function-declaration",
            "-Wno-error=int-conversion",
            "-Wno-error=attributes"
        ]
        
        self.conf.define("tools.build:cflags", compat_flags_c)
        self.conf.define("tools.build:cxxflags", compat_flags_cxx)
        
        self.dependencies["sdl"].cpp_info.set_property("cmake_target_name", "SDL2::SDL2")
        self.dependencies["sdl_ttf"].cpp_info.set_property("cmake_target_name", "SDL2_ttf::SDL2_ttf")
        for name, comp in self.dependencies["sdl_ttf"].cpp_info.components.items():
            comp.set_property("cmake_target_name", "SDL2_ttf::SDL2_ttf")
            comp.set_property("cmake_target_aliases", ["SDL2_ttf::SDL2_ttf"])
        
        self.dependencies["sdl_image"].cpp_info.set_property("cmake_target_name", "SDL2_image::SDL2_image")
        for name, comp in self.dependencies["sdl_image"].cpp_info.components.items():
            comp.set_property("cmake_target_name", "SDL2_image::SDL2_image")
            comp.set_property("cmake_target_aliases", ["SDL2_image::SDL2_image"])
            
        self.dependencies["sdl_mixer"].cpp_info.set_property("cmake_target_name", "SDL2_mixer::SDL2_mixer")
        for name, comp in self.dependencies["sdl_mixer"].cpp_info.components.items():
            comp.set_property("cmake_target_name", "SDL2_mixer::SDL2_mixer")
            comp.set_property("cmake_target_aliases", ["SDL2_mixer::SDL2_mixer"])

        from conan.tools.cmake import CMakeDeps, CMakeToolchain
        deps = CMakeDeps(self)
        deps.generate()
        tc = CMakeToolchain(self)
        tc.generate()

        import os
        # Append alias for SDL2_ttf
        ttf_targets = os.path.join(self.generators_folder, "SDL2_ttfTargets.cmake")
        if os.path.exists(ttf_targets):
            with open(ttf_targets, "a") as f:
                f.write("\nif(TARGET SDL2_ttf::SDL2_ttf-static AND NOT TARGET SDL2_ttf::SDL2_ttf)\n")
                f.write("    add_library(SDL2_ttf::SDL2_ttf ALIAS SDL2_ttf::SDL2_ttf-static)\n")
                f.write("endif()\n")
        
        # Append alias for SDL2_image
        img_targets = os.path.join(self.generators_folder, "SDL2_imageTargets.cmake")
        if os.path.exists(img_targets):
            with open(img_targets, "a") as f:
                f.write("\nif(TARGET SDL2_image::SDL2_image-static AND NOT TARGET SDL2_image::SDL2_image)\n")
                f.write("    add_library(SDL2_image::SDL2_image ALIAS SDL2_image::SDL2_image-static)\n")
                f.write("endif()\n")

        # Append alias for SDL2_mixer
        mix_targets = os.path.join(self.generators_folder, "SDL2_mixerTargets.cmake")
        if os.path.exists(mix_targets):
            with open(mix_targets, "a") as f:
                f.write("\nif(TARGET SDL2_mixer::SDL2_mixer-static AND NOT TARGET SDL2_mixer::SDL2_mixer)\n")
                f.write("    add_library(SDL2_mixer::SDL2_mixer ALIAS SDL2_mixer::SDL2_mixer-static)\n")
                f.write("endif()\n")

    def build_requirements(self):
        self.tool_requires("m4/1.4.19")