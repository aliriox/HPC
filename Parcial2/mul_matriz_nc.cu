#include <stdio.h>
#include <stdlib.h>
#include <cuda.h>
#include "archivos_csv.c"
#include <time.h>


__global__ void KernelGPU(float *d_a, float *d_b, float *d_c,int f1, int M, int c2){

	int i = threadIdx.y + blockDim.y * blockIdx.y;
	int j = threadIdx.x + blockDim.x * blockIdx.x;
	
	if(i < f1 && j <  c2){
		float Pvalue = 0.0;
		for(int k = 0; k < M; k++){
			Pvalue += d_a[i*M+k] * d_b[k*c2+j];
		}
		d_c[i * c2 + j] = Pvalue;
	}
}


void createVector(float *a, int f1, float *b, int c2, int inteM, float *c){

	// definiendo variables y reservando memoria

	float *d_a, *d_b, *d_c;
	int blocksize = 32;	

	cudaMalloc((void**)&d_a, f1 * inteM * sizeof(float));
	cudaMemcpy(d_a, a, f1 * inteM * sizeof(float), cudaMemcpyHostToDevice);

	cudaMalloc((void**)&d_b, inteM * c2 * sizeof(float));
	cudaMemcpy(d_b, b, inteM * c2 * sizeof(float), cudaMemcpyHostToDevice);

	cudaMalloc((void**)&d_c, f1 * c2 * sizeof(float));

	dim3 dimBlock(blocksize , blocksize , 1);
	dim3 dimGrid(ceil(inteM/float(blocksize)),ceil(f1/float(blocksize)),1);


	KernelGPU<<< dimGrid, dimBlock>>>(d_a,d_b,d_c,f1,inteM,c2);

	cudaMemcpy(c,d_c, f1 * c2 * sizeof(float), cudaMemcpyDeviceToHost);
	
	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_c);

}

int main(int argc, char *argv[]){

	if(argc != 3){
		printf("no se han ingresado los archivos necesarios\n");
	}

	FILE *fp;
	fp = fopen(argv[1], "r");

	if(fp==NULL){
		fputs("File error",stderr);
		return 1;
	}
	fclose(fp);
	
	fp = fopen(argv[2], "r");

	if(fp == NULL){
		fputs("file error", stderr);
		return 1;
	}
	fclose(fp);

	int Rows_1 = Detected_rows(fp,argv[1]);
	int Columns_1 = Detected_columns(fp,argv[1]);

	int Rows_2 = Detected_rows(fp,argv[2]);
	int Columns_2 = Detected_columns(fp,argv[2]);

	if(Columns_1 != Rows_2){
		printf("las matrizes no cumplen los requisitos para la multiplicacion entre estas");
		return 1;
	}

	int inteM = Columns_1;	
	
	float *Matriz1 = (float*)malloc(Rows_1 * inteM * sizeof(float));
	float *Matriz2 = (float*)malloc(inteM * Columns_2 * sizeof(float));
	float *MatrizR = (float*)malloc(Rows_1 * Columns_2 * sizeof(float));

	ExtracData(fp, Matriz1,argv[1],Rows_1,inteM);
	ExtracData(fp, Matriz2,argv[2],inteM,Columns_2);
	
	printf("Matriz 1: \n");
	printMatriz(Matriz1,Rows_1, inteM);
	printf("\n");
	printf("matriz 2: \n");
	printMatriz(Matriz2,inteM,Columns_2);
	printf("\n");

	time_inicial = clock();
	createVector(Matriz1,Rows_1,Matriz2,Columns_2,inteM,MatrizR);
	time_final = clock();

	printf("tiempo de ejecucion: %f\n", (time_final-time_inicial/CLOCKS_PER_SEC));

	printf("matriz Respuesta: \n");
	printMatriz(MatrizR, Rows_1, Columns_2);
	printf("\n");

	free(Matriz1);
	free(Matriz2);
	free(MatrizR);	

	return 0;

}
