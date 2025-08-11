git submodule update --init --remote

mkdir build
cd build
cmake ..
make -j 4

