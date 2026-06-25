
.PHONY: clean build

build:
	cmake --build build --parallel $(nproc)

clean:
	cmake --build build --target clean

config:
	cmake -S . -B build