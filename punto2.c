#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void EscribirArchivo(float *vector,char nombre[], int TamanioVector){

	FILE *fp;
	fp = fopen (nombre,"w");

	for(int i = 0; i < TamanioVector; i++){
		char array[10];
		sprintf(array, "%f", vector[i]);
		fputs(array, fp);
		fputs(";", fp);
	}

	fclose(fp);

}

int main(){

	int TamanioMatriz;
	float ** Matriz1;
	float ** Matriz2;
	float ** SumaVector;

	printf("Ingrese el tamanio del vector: \n");
	scanf("%d",&TamanioMatriz);

	Matriz1 = (float**) malloc (TamanioMatriz*sizeof(float*));
	Matriz2 =  (float**) malloc (TamanioMatriz*sizeof(float*));

	if(Matriz1 == NULL || Matriz2 == NULL){
		printf("error reservando memoria malloc");
		exit(1);
	}

	for(int i = 0; i < TamanioMatriz; i++){
		Matriz1[i] = (float*) malloc (TamanioMatriz*sizeof(float));
		Matriz2[i] = (float*) malloc (TamanioMatriz*sizeof(float));
	}

	
	float a = 1.0;
	for(int i = 0; i < TamanioMatriz; i++){
		for(int j = 0; j < TamanioMatriz; j++){
			float num = ((float)rand()/(float)(RAND_MAX) * a);
			Matriz1[i][j] = num;
		}
	}

	for(int i = 0; i < TamanioVector; i++){
		for(int j = 0; j < TamanioMatriz; j++){
			float num = ((float)rand()/(float)(RAND_MAX) * a);
			Matriz2[i][j] = num;
		}
	}
	

	EscribirArchivo(Vector1,"entrada1.csv", TamanioVector);
	EscribirArchivo(Vector2,"entrada2.csv", TamanioVector);

	SumaVector = (float*) malloc (TamanioVector*sizeof(float));
	for(int i = 0; i < TamanioVector; i++){
		SumaVector[i] = Vector1[i] + Vector2[i];
	}

	EscribirArchivo(SumaVector,"resultado.csv", TamanioVector);

	free(Vector1);
	free(Vector2);
	free(SumaVector);
	return 0;

}