cmake -S . -B build \
      -DCMAKE_TOOLCHAIN_FILE=build/RelWithDebInfo/generators/conan_toolchain.cmake \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# 3. Symlink for clangd (Crucial for EndeavourOS/Linux)
ln -sf build/compile_commands.json .
