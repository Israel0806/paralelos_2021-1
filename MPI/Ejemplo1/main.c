#include <stdio.h>
#include "mpi.h"

int main() {
    int my_rank, comm_sz;
    int arr[] = {1,2,3,4,5,6,7,8,9,10,11,12};
    int arr_size = 12;
	int local_sum = 0;
    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    if(my_rank != 0){
        int range = arr_size / (comm_sz-1);
        int range_min = (my_rank - 1) * range;
        int range_max = (my_rank - 1) * range + range;
        for (int i = range_min; i < range_max; ++i)
            local_sum += arr[i];
        printf("Suma local: %i", local_sum);
        MPI_Send(&local_sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    } else {
		int total_sum = 0;
        for (int i= 1; i < comm_sz; ++i){
            MPI_Recv(&local_sum, 1, MPI_INT,i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            total_sum += local_sum;
        }
		printf("The total Sum of the array is: %i\n", total_sum);
    }
    MPI_Finalize();
	return 0;
}
