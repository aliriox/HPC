#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#include<cuda.h>
#include<string.h>

__global__
void multiplicationKernell(float* m1, float* m2, float* m3, int rowsM1, int colsM2)
{
    int Row = blockIdx.y * blockDim.y + threadIdx.y;
    int Col = blockIdx.x * blockDim.x + threadIdx.x;

    if((Row < rowsM1) && (Col < colsM2))
    {
        float resul = 0.0;
        for(int i = 0; i < rowsM1; i++)
        {
            resul = resul + m1[Row*rowsM1+i] * m2[i*rowsM1+Col];
        }
        m3[Row*rowsM1+Col] = resul;
    }

}

__host__
void toMatrix(float *M, FILE *content, int rows, int cols)
{
    for(int i=0; i<rows;i++)
    {
        for(int j=0; j<cols; j++)
        {
            fscanf(content,"%f",&M[i*cols+j]);
        }
    }
    fclose(content);
}

__host__
void print(float *M, int rows, int cols)
{
    printf("----------MATRIX----------\n");
    for(int i=0; i<rows;i++)
    {
        for(int j=0; j<cols; j++)
        {
            printf("[%f]",M[i*cols+j]);
        }
        printf("\n");
    }
}


int main(int argc, char** argv)
{
    if(argc != 3)
    {
        printf("Error, no se encontraron todos los parametros necesarios.");
        return 1;
    }

    FILE *inputMatrix1;
    FILE *inputMatrix2;

    inputMatrix1 = fopen(argv[1],"r");
    inputMatrix2 = fopen(argv[2],"r");

    float *m1, *m2, *m3;
    int rowsM1, rowsM2, colsM1, colsM2, rowsM3, colsM3;
    
    fscanf(inputMatrix1,"%d",&rowsM1);
    fscanf(inputMatrix1,"%d",&colsM1);

    fscanf(inputMatrix2,"%d",&rowsM2);
    fscanf(inputMatrix2,"%d",&colsM2);

    m1 = (float*) malloc(rowsM1*colsM1*sizeof(float));
    m2 = (float*) malloc(rowsM2*colsM2*sizeof(float));
    m3 = (float*) malloc(rowsM1*colsM2*sizeof(float));
    
    toMatrix(m1, inputMatrix1, rowsM1, colsM1);
    toMatrix(m2, inputMatrix2, rowsM2, colsM2);
    print(m1, rowsM1, colsM1);
    print(m2, rowsM2, colsM2);

    if((rowsM1 != colsM2))
    {
        printf("Error los tamaños de las matrices no son compatibles.");
        return 1;
    }

    //Para el Devince
    cudaError_t error = cudaSuccess;
    float *d_m1, *d_m2, *d_m3;
    int blockSize = 32;

    dim3 dimBlockSize(blockSize,blockSize,1);
    dim3 dimGridSize(ceil(colsM1 / float(blockSize)), ceil(rowsM1 / float(blockSize)), 1);

    error = cudaMalloc((void**)&d_m1, rowsM1 * colsM1 * sizeof(float));
    if(error != cudaSuccess)
    {
        printf("Imposible asignar memoria para d_m1");
        return 1;
    }

    error = cudaMalloc((void**)&d_m2, rowsM2 * colsM2 * sizeof(float));
    if(error != cudaSuccess)
    {
        printf("Imposible asignar memoria para d_m2");
        return 1;
    }

    error = cudaMalloc((void**)&d_m3, rowsM3 * colsM3 * sizeof(float));
    if(error != cudaSuccess)
    {
        printf("Imposible asignar memoria para d_m3");
        return 1;
    }

    cudaMemcpy(d_m1, m1, rowsM1 * colsM1 * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_m2, m2, rowsM2 * colsM2 * sizeof(float), cudaMemcpyHostToDevice);

    multiplicationKernell<<<dimGridSize, dimBlockSize>>>(d_m1, d_m2, d_m3, rowsM1, colsM2);


    cudaMemcpy(m3, d_m3, rowsM1 * colsM2 * sizeof(float), cudaMemcpyDeviceToHost);
    print(m3, rowsM1, colsM2);

    free(m1);
    free(m2);
    free(m3);

    cudaFree(d_m1);
    cudaFree(d_m2);
    cudaFree(d_m3);

    return 0;
}