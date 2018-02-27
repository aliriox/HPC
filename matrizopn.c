#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define TamanioMatriz 100000

double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b){
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
}

void EscribirArchivo(float **Matriz,char nombre[]){

	FILE *fp;
	fp = fopen (nombre,"w");

	for(int i = 0; i < TamanioMatriz; i++){
		for(int j = 0; j < TamanioMatriz; j++){
			char array[10];
			sprintf(array, "%f", Matriz[i][j]);
			fputs(array, fp);
			fputs(";", fp);
		}
		fputs("\n", fp);
	}

	fclose(fp);

}

int main(){

	float ** Matriz1;
	float ** Matriz2;
	float ** Resultado;
	LARGE_INTEGER t_ini, t_fin;
	double secs;

	Matriz1 = (float**) malloc (TamanioMatriz*sizeof(float*));
	Matriz2 =  (float**) malloc (TamanioMatriz*sizeof(float*));
	Resultado = (float**) malloc (TamanioMatriz*sizeof(float*));

	if(Matriz1 == NULL || Matriz2 == NULL || Resultado == NULL){
		printf("error reservando memoria malloc filas");
		exit(1);
	}

	for(int i = 0; i < TamanioMatriz; i++){
		Matriz1[i] = (float*) malloc (TamanioMatriz*sizeof(float));
		Matriz2[i] = (float*) malloc (TamanioMatriz*sizeof(float));
		Resultado[i] = (float*) malloc (TamanioMatriz*sizeof(float));
		if(Matriz1[i] == NULL || Matriz2[i] == NULL || Resultado[i] == NULL){
			printf("error reservando memoria malloc columnas");
			exit(1);
		}
	}

	// llenar matrizes con valores aleatorios

	float a = 1.0;
	for(int i = 0; i < TamanioMatriz; i++){
		for(int j = 0; j < TamanioMatriz; j++){
			float num = ((float)rand()/(float)(RAND_MAX) * a);
			Matriz1[i][j] = num;
		}
	}

	for(int i = 0; i < TamanioMatriz; i++){
		for(int j = 0; j < TamanioMatriz; j++){
			float num = ((float)rand()/(float)(RAND_MAX) * a);
			Matriz2[i][j] = num;
		}
	}


	// multiplicacion de matrizes	

	QueryPerformanceCounter(&t_ini);
	for (int i = 0;i < TamanioMatriz; i++){
		for (int j = 0;j < TamanioMatriz; j++){
			Resultado[i][j]=0;
         	for (int k = 0;k < TamanioMatriz; k++){
         		Resultado[i][j] = Resultado[i][j] + Matriz1[i][k] * Matriz2[k][j];
          	}
       	}
    }
    QueryPerformanceCounter(&t_fin);

	// mostrar matrizes

    EscribirArchivo(Resultado,"resultadoMatrizOpenMP.csv");


    // mostramos el tiempo de ejecucion del programa

    secs = performancecounter_diff(&t_fin, &t_ini);
  	printf("%.16g milliseconds\n", secs * 1000.0);


  	// liberar memoria
	for(int i = 0; i < TamanioMatriz; i++){
		free(Matriz1[i]);
		free(Matriz2[i]);
		free(Resultado[i]);
	}
	free(Matriz1);
	free(Matriz2);
	free(Resultado);
	return 0;

}