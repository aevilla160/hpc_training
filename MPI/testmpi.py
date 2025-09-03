from mpi4py import MPI

# Initialize the MPI communicator
comm = MPI.COMM_WORLD

# Get the rank of the process
rank = comm.Get_rank()

# Get the total number of processes
size = comm.Get_size()

# Main script logic
if rank == 0:
    # Code for rank 0 (usually the "master" or "root" rank)
    data_to_send = "Hello from Rank 0"
    for i in range(1, size):
        comm.send(data_to_send, dest=i, tag=11)
        print(f"Rank 0 sent data to Rank {i}")
else:
    # Code for all other ranks (workers)
    received_data = comm.recv(source=0, tag=11)
    print(f"Rank {rank} received data: {received_data}")

# Finalize the MPI environment (not necessary in mpi4py but good for clarity)
MPI.Finalize()
