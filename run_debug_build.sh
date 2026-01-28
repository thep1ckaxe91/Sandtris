cd $(dirname $0)

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug || exit 1

cd build

cmake --build . -j $(nproc | tr -d '\n') || exit 1

./Sandtris
