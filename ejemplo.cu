#include<stdio.h>
#include<stdlib.h>
#include<cuda.h>

#define n 10

__global__ void KernelGPU(float *d_a){

        int i = threadIdx.y + blockDim.y * blockIdx.y;
        int j = threadIdx.x + blockDim.x * blockIdx.x;

        if(i < n && j <  n){
                d_a[i*n+j] = d_a[i*n+j] * 5.0;
        }


}


void createVector(float *a){

        // definiendo variables y reservando memoria

        float *d_a;
        int blocksize = 10;

        cudaMalloc((void**)&d_a,n * n * sizeof(float));
        cudaMemcpy(d_a, a, n * n * sizeof(float), cudaMemcpyHostToDevice);

        dim3 dimBlock(n , n , 1);
	dim3 dimGrid(ceil(n/float(blocksize)),ceil(n/float(blocksize)),1);


        KernelGPU<<< dimGrid, dimBlock>>>(d_a);

        // funcion para liberar memoria
        cudaMemcpy(a,d_a, n * n * sizeof(float), cudaMemcpyDeviceToHost);

        cudaFree(d_a);

}

int main(){

        float *a;

	a = (float *)malloc(n * n *sizeof(float));

        for(int i = 0; i < n * n; i++){
                a[i] = 1.0;
        }

        createVector(a);

        for(int i = 0; i < n; i++){
                for(int j = 0; j < n; j++){
                        printf("[%f]",a[i*n+j]);
                }
                printf("\n");
        }

        return 0;

}


