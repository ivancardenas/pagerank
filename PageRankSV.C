#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <random>
#include <vector>
#include <mpi.h>

using namespace std;

int main(int argc, char** argv) {
	
	if (argc < 4) {
		cout << "Usage: PageRank [length]" <<
			 " [density] [tolerance]" << endl;
		return 0;
	}
	
	int length = atoi(argv[1]);
	double density = atof(argv[2]);
	double tolerance = atof(argv[3]);

	double matrix[length][length];
	double auxiliary[length];
	double value, addition;

	vector<float> values, r, times;
	vector<int> columns, pointerB, pointerE;

	MPI_Init(NULL, NULL);
	
	int workers, rank, name_length;
	
	MPI_Comm_size(MPI_COMM_WORLD, &workers);
	
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	char processor[MPI_MAX_PROCESSOR_NAME];
	
	MPI_Get_processor_name(processor, &name_length);

	
	srand(time(NULL));

	// -------- Matrix Creation. --------
	for (int i = 0; i < length; i++) {
      
		addition = 0;
      
		for (int j = 0; j < length; j++) {
         
			double result = (double) rand() / (RAND_MAX);
         
			if (i == j) value = 0;
			else if (result < density)
				value = (double) rand() / (RAND_MAX);
			else value = 0;

			/* if (addition + value > 1)	value = 0;

			// Last cell = 0
			if (j == (length - 2) 
					&& i == (length - 1))
				value = 1.0 - addition;
			else if (j == (length - 2) 
					&& i == (length - 1))
				value = 0;

			if (j == (length - 1))
				value = 1.0 - addition; */
	
			addition += value;

			matrix[j][i] = value;
		}
		
		auxiliary[i] = addition;
	}
	
	for (int i = 0; i < length; i++)
		for (int j = 0; j < length; j++)
			if (matrix[j][i] != 0)
				matrix[j][i] = matrix[j][i] / auxiliary[i];

	// -------- Print Matrix. --------
	/* for (int i = 0; i < length; i++) {
		for(int j = 0; j < length; j++) 
			cout << matrix[i][j] << " | ";
		cout << endl;
	} */

	// -------- Sparse Matrix - CSR. --------
	int position = 0, counter = 0;
	
	for (int i = 0; i < length; i++) {
			
			pointerB.push_back(position);
      
			for (int j = 0; j < length; j++) {
         
				if (matrix[i][j] != 0) {
					
					counter++;
					values.push_back(matrix[i][j]);
					columns.push_back(j);
					position++;
				}
			}
			
			pointerE.push_back(position);
	}

	// -------- Filling Vector (r) --------
	double probability = (double)( 1.0 / (double) length);
	
	for (int i = 0; i < length; i++) {
		r.push_back(probability);
		times.push_back(0.0);
	}
	
	// -------- Matrix x Vector (r) --------
	for (int i = 0; i < length; i++) 
		for (int j = pointerB[i]; j < pointerE[i]; j++)
			times[i] += (values[j] * r[columns[j]]);


	MPI_Finalize();
}
