.DEFAULT_GOAL := relwithdebinfo_build

.PHONY: all relwithdebinfo_build release_build debug_build \
				install_rwdi install_db install_rel clean distclean \
				hotspot

# Default alias
all: relwithdebinfo_build

# Conan dependency generation
install_rwdi:
	conan install . --build=missing -s build_type=RelWithDebInfo

install_db:
	conan install . --build=missing -s build_type=Debug

install_rel:
	conan install . --build=missing -s build_type=Release

relwithdebinfo_build: install_rwdi
	cmake --preset conan-relwithdebinfo
	cmake --build --preset conan-relwithdebinfo

release_build: install_rel
	cmake --preset conan-release
	cmake --build --preset conan-release

debug_build: install_db
	cmake --preset conan-debug
	cmake --build --preset conan-debug

clean:
	@if [ -d "build/RelWithDebInfo" ]; then cmake --build --preset conan-relwithdebinfo --target clean; fi
	@if [ -d "build/Debug" ]; then cmake --build --preset conan-debug --target clean; fi
	@if [ -d "build/Release" ]; then cmake --build --preset conan-release --target clean; fi

hotspot: relwithdebinfo_build
	sudo perf record --call-graph dwarf -F 99 ./build/RelWithDebInfo/Sandtris
	hotspot ./perf.data

# Full purge of generated trees and presets
distclean:
	rm -rf build/ CMakeUserPresets.json
