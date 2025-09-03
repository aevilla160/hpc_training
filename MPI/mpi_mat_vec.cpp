#include <mpi.h>
#include <iostream>
#include <cstring>

int main(int argc, char* argv[]) {
    // Initialize MPI program
    MPI_Init(&argc, &argv);
    
    // Get the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    
    // Get the total number of processes
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Initialize matrix and vector
        int matrix[9][9];
        int vector[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        int results[9] = {0}; // Array to store final results
        
        // Initialize matrix with your values
        for(int i = 0; i < 9; i++) {
            for(int j = 0; j < 9; j++) {
                matrix[i][j] = i + j;
            }
        }

        // Send data to worker processes
        for (int i = 1; i < size; i++) {
            // Send one row to each process
            MPI_Send(matrix[i-1], 9, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(vector, 9, MPI_INT, i, 1, MPI_COMM_WORLD);
            std::cout << "Rank 0 sent data to Rank " << i << std::endl;
        }

        // Receive results from workers
        for (int i = 1; i < size; i++) {
            int partial_result;
            MPI_Recv(&partial_result, 1, MPI_INT, i, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            results[i-1] = partial_result;
        }

        // Print results
        std::cout << "Matrix-vector multiplication results:" << std::endl;
        for(int i = 0; i < 9; i++) {
            std::cout << "Row " << i << ": " << results[i] << std::endl;
        }
    } 
    else {
        // Worker processes
        int row[9];
        int vector[9];
        int result = 0;

        // Receive row and vector
        MPI_Recv(row, 9, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(vector, 9, MPI_INT, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // Compute partial result (dot product of row and vector)
        for(int i = 0; i < 9; i++) {
            result += row[i] * vector[i];
        }

        // Send result back to rank 0
        MPI_Send(&result, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
        std::cout << "Rank " << rank << " computed result: " << result << std::endl;
    }

    // Finalize MPI
    MPI_Finalize();
    return 0;
}
