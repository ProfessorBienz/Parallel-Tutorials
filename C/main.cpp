// This include is required for tutorial to pass tests
#include "src.hpp"

int tutorial_main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);

    printf("hello world!\n");

    MPI_Finalize();
    return 0;

}
