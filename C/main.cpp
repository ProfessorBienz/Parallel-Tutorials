// This include is required for tutorial to pass tests
#include "src.hpp"
#include <time.h>
#include <vector>

void transpose(double* A, double* AT, int local_n, int global_n)
{
    int rank, num_procs;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

    double* send_buffer = new double[local_n*global_n];
    double* recv_buffer = new double[local_n*global_n];
    
    MPI_Request* send_requests = new MPI_Request[num_procs];
    MPI_Request* recv_requests = new MPI_Request[num_procs];

    int tag = 1024;

    int msg_size = local_n*local_n; // size of each msg
                                    //
    for (int i = 0; i < num_procs; i++)
    {
        MPI_Irecv(&(recv_buffer[i*msg_size]), msg_size, MPI_DOUBLE, i, tag, MPI_COMM_WORLD,
                &(recv_requests[i]));
    }

    int ctr = 0;
    for (int i = 0; i < num_procs; i++)
    {
        for (int col = i*local_n; col < (i+1)*local_n; col++)
        {
            for (int row = 0; row < local_n; row++)
            {
                send_buffer[ctr++] = A[row*global_n+col];
            }
        }
        MPI_Isend(&(send_buffer[i*msg_size]), msg_size, MPI_DOUBLE, i, tag, MPI_COMM_WORLD,
                &(send_requests[i]));
    }
    
    MPI_Waitall(num_procs, send_requests, MPI_STATUSES_IGNORE);
    MPI_Waitall(num_procs, recv_requests, MPI_STATUSES_IGNORE);

    for (int row = 0; row < local_n; row++)
    {
        for (int i = 0; i < num_procs; i++)
        {
            for (int col = 0; col < local_n; col++)
            {
                AT[row*global_n + i*local_n + col] = recv_buffer[i*local_n*local_n + row*local_n + col];
            }
        }
    }

    delete[] send_buffer;
    delete[] recv_buffer;
    delete[] send_requests;
    delete[] recv_requests;
}

void transpose_datatype(double* A, double* AT, int local_n, int global_n)
{
}

void transpose_alltoall(double* A, double* AT, int local_n, int global_n)
{
}


// Initialize, create random, finalize, and return
int tutorial_main(int argc, char* argv[])
{
    // 1. Initialize
    
    // 2. Perform an alltoall
    
    // 3. Compare your methods
    
    // 4. Finalize

    return 0;
}
