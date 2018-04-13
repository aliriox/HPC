#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
/*#include<cuda.h>*/
#include<string.h>

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

void multiplication(float *m1, float *m2, float *m3, int rowsM1, int colsM1, int rowsM2, int colsM2)
{
    for(int i=0; i<rowsM1; i++)
    {
        for(int j=0; j<colsM1; j++)
        {
            m3[i*colsM1+j] = 0.0;
            for(int k=0; k<colsM1; k++)
            {
                m3[i*colsM1+j] = m3[i*colsM1+j] + m1[i*colsM1+k] * m2[k*colsM1+j];
            }
        }
            
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
    int rowsM1, rowsM2, colsM1, colsM2;
    
    fscanf(inputMatrix1,"%d",&rowsM1);
    fscanf(inputMatrix1,"%d",&colsM1);

    fscanf(inputMatrix2,"%d",&rowsM2);
    fscanf(inputMatrix2,"%d",&colsM2);

    //Memoria el Para Host
    m1 = (float*) malloc(rowsM1*colsM1*sizeof(float));
    m2 = (float*) malloc(rowsM2*colsM2*sizeof(float));
    m3 = (float*) malloc(rowsM1*colsM2*sizeof(float));
    
    toMatrix(m1, inputMatrix1, rowsM1, colsM1);
    toMatrix(m2, inputMatrix2, rowsM2, colsM2);
    print(m1, rowsM1, colsM1);
    print(m2, rowsM2, colsM2);

    if((rowsM1 == colsM2))
    {
        multiplication(m1,m2,m3,rowsM1, colsM1, rowsM2, colsM2);        
    }
    else
    {
        printf("Error los tamaños de las matrices no son compatibles.");
        return 1;
    }

    print(m3,rowsM1,colsM2);
        
    return 0;
}