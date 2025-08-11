#include "src.hpp"

int main(int argc, char* argv[])
{
    PMPI_Init(&argc, &argv);

    int rank, num_procs;
    PMPI_Comm_rank(MPI_COMM_WORLD, &rank);
    PMPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    tutorial_main(argc, argv);

    PMPI_Finalize();
    return 0;
}
