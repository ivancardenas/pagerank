#include <stdio.h>
#include <mpi.h>

int main(int argc, char** argv) {
	
	MPI_Init(NULL, NULL);
	
	int workers; // World size.
	MPI_Comm_size(MPI_COMM_WORLD, &workers);
	
	int rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	char processor[MPI_MAX_PROCESSOR_NAME];
	
	int name_length;
	MPI_Get_processor_name(processor, &name_length);

	printf("Hello world from processor %s, rank %d"
           " out of %d processors\n",
           processor, rank, workers);
	

	
	MPI_Finalize();
}
