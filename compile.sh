## For codespaces, needed since ProfBienz owns the src submodule
git config --global --add safe.directory "$(pwd)"/src

## Update the src folder with current remote submodule
git submodule update --init --remote

## Make build folder and compile code
mkdir build
cd build
cmake ..
make -j 4

