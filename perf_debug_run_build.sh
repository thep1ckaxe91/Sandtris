cd $(dirname $0)

cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -S . -B build || exit 1

cd build

cmake --build . -j $(nproc | tr -d '\n') || exit 1

cd ..

perf record -g --call-graph dwarf ./build/Sandtris