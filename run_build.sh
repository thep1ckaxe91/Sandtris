cd $(dirname $0)

cmake -S . -B build || exit 1

cd build

cmake --build . -j $(nproc | tr -d '\n') || exit 1

./Sandtris