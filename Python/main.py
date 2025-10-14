from mpi4py import MPI
import numpy as np

def transpose(A, AT, local_n, global_n):
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    num_procs = comm.Get_size()
    tag = 0

    msg_size = local_n * local_n
    total = local_n * global_n

    A  = np.asarray(A,  dtype='d').reshape(-1)
    AT = np.asarray(AT, dtype='d').reshape(-1)
    buffer = np.empty(total, dtype='d')

    recv_requests = []
    for i in range(num_procs):
        recv_requests.append(comm.Irecv(AT[i*msg_size:(i+1)*msg_size], source=i, tag=tag))

    send_requests = []
    ctr = 0
    for i in range(num_procs):
        for j in range(i * local_n, (i + 1) * local_n):
            for k in range(local_n):
                buffer[ctr] = A[j * local_n + k]
                ctr += 1
        send_requests.append(comm.Isend(buffer[i*msg_size:(i+1)*msg_size], dest=i, tag=tag))

    MPI.Request.Waitall(send_requests)
    MPI.Request.Waitall(recv_requests)

    return AT 


def transpose_datatype(A, AT, local_n, global_n):


def transpose_alltoall(A, AT, local_n, global_n):


def main():

