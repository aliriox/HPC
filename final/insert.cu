#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

__global__ void insert(int *a, int t){

	int i = blockIdx.x*blockDim.x+threadIdx.x;

	if(i < t-1){
		for(int k = 0; k < t-1; k++){
			if(a[k] > a[k+1]){
				int aux = a[k];
				a[k] = a[k+1];
				a[k+1] = aux;
			}
		}
	}

}

void imp(int *a, int n){
	for(int i = 0; i < n; i++){
		cout << a[i]<<endl;
	}
	cout<<endl<<endl;
}

void cuda(int *a, int n){

	int *array;

	cudaMalloc((void**)&array, n * sizeof(int));
	cudaMemcpy(array,a,n * sizeof(int),cudaMemcpyHostToDevice);

	cout<< "entro al kernel" <<endl;

	insert<<<1024,1>>>(array,n);

	cout<<"salgo del kernel"<<endl;
	
	cudaMemcpy(a,array,n * sizeof(int),cudaMemcpyDeviceToHost);
	
	cout<<"libero memoria"<<endl;
	
	cudaFree(array);

}

int main(){

	int n;
	cin >> n;

	int a[n];
	int *vec;
        vec = (int*)malloc(n*sizeof(int));

	for(int i = 0; i < n; i++){
		cin >> a[i];
		vec[i] = a[i];
	}
	
	cuda(vec,n);

	imp(vec,n);

	free(vec);
	return 0;
}
