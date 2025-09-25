// This include is required for tutorial to pass tests
#include "src.hpp"
#include <time.h>
#include <vector>


// Tutorial Part 1
// Simple allgather 
double allgather_simple(double* sendbuf, double* recvbuf, int size)
{
    // Everyone sends `sendbuf` to process `0`

    // Process `0` receives from everyone into `recvbuf`

    // Process '0' sends 'recvbuf' to everyone
}

// Tutorial Part 2
// Simple allgather: At step i, send to rank - i and recv from rank + i
double allgather_pairwise(double* sendbuf, double* recvbuf, int size)
{    
    // Copy local send_array into recv_array[rank*N]
    
    // For loop that iterates over each other process
    //      1. Send to process rank - i
    //      2. Recv from process rank + i

}

// Tutorial Part 3
// Perform an allgather through a ring algorithm:
// At each step, send data that originated on rank+i to rank - 1
// and recv data that originated on rank - (i+1)
double allgather_ring(double* sendbuf, double* recvbuf, int size)

{
    // Copy local send_array into recv_array[rank*N]

    // For loop that iterates over each other process
    //      1. Send recv_array[(rank-i)*N] to rank - 1
    //      2. Recv into recv_array[(
}

// Initialize, create random, finalize, and return
int tutorial_main(int argc, char* argv[])
{
    // 1. Initialize
    
    // 2. Time your methods
    
    // 3. Print out the time to perform each method

    // 4. Finalize

    return 0;
}
