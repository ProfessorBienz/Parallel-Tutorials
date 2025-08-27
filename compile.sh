git submodule update --init --remote

mkdir build
cd build
cmake -DUSE_PY=ON ..
#cmake ..
make -j 4

