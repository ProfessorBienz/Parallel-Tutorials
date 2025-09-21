// This include is required for tutorial to pass tests
#include "src.hpp"
#include <time.h>
#include <vector>


// Tutorial Part 1
double send_recv_random()
{
    // Rank 0 seeds random number generator
    
    // Rank 0 gets a random number

    // Rank 0 sends random number to Rank 1

    // Both ranks return the same random number
}

// Tutorial Part 2
// Perform a ping-pong with MPI_Send and MPI_Recv
void ping_pong_send_and_recv(int N, double* send_array, double* recv_array)
{    
    // Fill send_array with unique random numbers

    // Rank 0 sends send_array to Rank 1
    // Rank 1 receives into its recv_array

    // Rank 1 sends send_array to Rank 0
    // Rank 0 recieves into its recv_array

}

// Tutorial Part 3
// Perform a ping-pong with MPI_Sendrecv
void ping_pong_sendrecv(int N, double* send_array, double* recv_array)
{
    // Fill send_array with unique random numbers

    // Rank 0 sends send_array to Rank 1
    // Rank 1 receives into its recv_array

    // Rank 1 sends send_array to Rank 0
    // Rank 0 recieves into its recv_array

}

// Initialize, create random, finalize, and return
int tutorial_main(int argc, char* argv[])
{
    // 1. Initialize
    
    // 2. Call your methods

    // 3. Finalize

    return 0;
}
