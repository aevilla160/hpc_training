#include <mpi.h>
#include <iostream>

int main(int argc, char* argv[]) {
    
	
    //Initiatilizes MPI program by recieving arguements
    MPI_Init(&argc, &argv);
    
    // Get the rank of the process
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    // Get the total number of processes
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
    	int arr1[9][9];
    	int col[9] = {1,2,3,4,5,6,7,8,9};

    	for(int i = 0; i < 9; i++){
        	for(int j = 0; j < 9; j++){
           	int temp = i+j;
           	arr1[i][j]=temp;
       	   }
    	}


	 //if we have 8 ranks start at 0; 
	 //each rank does a row of the matrix vector work
        const char* message = "Hello from Rank 0";
        for (int i = 1; i < size; i++) {
            MPI_Send(arr1,9*9 , MPI_INT, i, 0, MPI_COMM_WORLD);
	    MPI_Send(col,9, MPI_INT, i, 0, MPI_COMM_WORLD);
            std::cout << "Rank 0 sent data to Rank " << i << std::endl;
        }
    } else {
        // Code for all other ranks (workers)
        int received_message[9][9];
	int recieved_column[9];
        MPI_Recv(received_message, 9*9, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	MPI_Recv(recieved_column, 9, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        std::cout << "Rank " << rank << " received data: " << received_message << std::endl;
	int result;
	for(int x = 0; x<size;x++){
		if(x == rank){
		for(int curcol = 1; curcol < 9; curcol++){
		result+= recieved_column[x]*received_message[x][curcol];
			}	
		}
		}
	std::cout<< result<< std::endl;
    }

    // Finalize the MPI environment
    MPI_Finalize();

    return 0;
}

