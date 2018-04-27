#include <mpi.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	
	int pad = 0, dimx = 480 + pad, dimy = 480, dimz = 400, nreps = 100;
	int pid=-1, np=-1;

	MPI_Init(&argc,&argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &pid);
	MPI_Comm_size(MPI_COMM_WORLD, &np);

	if(np < 3){
		if(0 == pid){ 
			printf("Needed 3 or more processes.\n");
			MPI_Abort( MPI_COMM_WORLD, 1);
			return 1;
		}
	}
	if(pid < np - 1){
		compute_process(dimx, dimy, dimz / (np -1), nreps);
	}else{
		data_server(dimx, dimy, dimz);
	}

	MPI_Finalize();
	return 0;

}