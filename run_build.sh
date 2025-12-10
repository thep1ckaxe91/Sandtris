cd $(dirname $0)

cmake -S . -B build || exit 1

cd build

ninja -j $(nproc | tr -d $'\n') || exit 1

./Sandtris