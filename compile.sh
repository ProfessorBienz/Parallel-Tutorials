## For codespaces, needed since ProfBienz owns the src submodule
git config --global --add safe.directory "$(pwd)"/src

## Update the src folder with current remote submodule
git submodule update --init --remote

## Make build folder and compile code
mkdir build
cd build

## If you want to use Python, switch which cmake statement is commented below
cmake ..
#cmake -DUSE_PY=ON ..

make -j 4

