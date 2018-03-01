#include <stdio.h>
#include <stdlib.h>
//#include <sys/time.h>
#include <time.h>
#include <omp.h>
//#include <windows.h>


#define TamanioMatriz 1500

//double performancecounter_diff(LARGE_INTEGER *a, LARGE_INTEGER *b){
//	LARGE_INTEGER freq;
//	QueryPerformanceFrequency(&freq);
//	return (double)(a->QuadPart - b->QuadPart) / (double)freq.QuadPart;
//}

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
	//LARGE_INTEGER t_ini, t_fin;
	//double secs;
	//struct timeval comienzo, final;

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
	
	printf("llenando matrizes...\n");

	float a = 1.0;
	for(int i = 0; i < TamanioMatriz; i++){
		for(int j = 0; j < TamanioMatriz; j++){
			float num = ((float)rand()/(float)(RAND_MAX) * a);
			float num2 = ((float)rand()/(float)(RAND_MAX) * a);
			Matriz1[i][j] = num;
			Matriz2[i][j] = num2;
		}
	}

	EscribirArchivo(Matriz1,"entrada1omp.csv");
	EscribirArchivo(Matriz2,"entrada2omp.csv");

	printf("fin de llenado... 100-P\n");
	printf("multiplicando matrizes...\n");
	// multiplicacion de matrizes	

	//QueryPerformanceCounter(&t_ini);
	//gettimeofday(&comienzo, NULL);
	double begin1 = omp_get_wtime( );

	for (int i = 0;i < TamanioMatriz; i++){
		for (int j = 0;j < TamanioMatriz; j++){
			Resultado[i][j]=0;
         	for (int k = 0;k < TamanioMatriz; k++){
         		Resultado[i][j] = Resultado[i][j] + Matriz1[i][k] * Matriz2[k][j];
          	}
       	}
    }

    double end1 = omp_get_wtime();
    //gettimeofday(&final, NULL);
    //QueryPerformanceCounter(&t_fin);

    printf("finalizacion de la multiplicacion sin paralelizar... 100-P\n");

    // mostramos el tiempo de ejecucion del programa

  	//printf("Duración del programa: %.16f \n", (final.tv_sec+(float)final.tv_usec/1000000)-(comienzo.tv_sec+(float)comienzo.tv_usec/1000000));
  	printf("Duración de la multiplicacion sin paralelizar: %.16f \n", end1 - begin1);

	printf ( "\n\n" );
	printf ( "Number of processors available = %d\n", omp_get_num_procs ( ) );
	printf ( "Number of threads =  %d\n\n", omp_get_max_threads ( ) );

    int i,j,k = 0;
	double begin2 = 0.0;

    # pragma omp parallel shared(Resultado,Matriz1,Matriz2) private(i,j,k)
    # pragma opm for

    begin2 = omp_get_wtime( );

	for (i = 0;i < TamanioMatriz; i++){
		for (j = 0;j < TamanioMatriz; j++){
			Resultado[i][j]=0;
         	for (k = 0;k < TamanioMatriz; k++){
         		Resultado[i][j] = Resultado[i][j] + Matriz1[i][k] * Matriz2[k][j];
          	}
       	}
    }

    double end2 = omp_get_wtime( );

    printf("finalizacion de la multiplicacion paralelizado... 100-P\n");

    // mostramos el tiempo de ejecucion del programa

  	//printf("Duración del programa: %.16f \n", (final.tv_sec+(float)final.tv_usec/1000000)-(comienzo.tv_sec+(float)comienzo.tv_usec/1000000));
  	printf("Duración de la multiplicacion paralelizado: %.16f \n", (end2 - begin2));

	// mostrar matrizes

    EscribirArchivo(Resultado,"resultadoMatrizOpenMP.csv");

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
