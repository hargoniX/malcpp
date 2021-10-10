mkdir -p build
cd build
export CC=$(which clang)
export CXX=$(which clang++)
cmake ../ -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
make
