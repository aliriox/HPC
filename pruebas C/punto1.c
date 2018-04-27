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

	int TamanioVector;
	float * Vector1;
	float * Vector2;
	float * SumaVector;

	printf("Ingrese el tamanio del vector: \n");
	scanf("%d",&TamanioVector);

	Vector1 = (float*) malloc (TamanioVector*sizeof(float));
	Vector2 =  (float*) malloc (TamanioVector*sizeof(float));

	if(Vector1 == NULL || Vector2 == NULL){
		printf("error reservando memoria malloc");
		exit(1);
	}

	float a = 1.0;
	for(int i = 0; i < TamanioVector; i++){
		float num = ((float)rand()/(float)(RAND_MAX) * a);
		Vector1[i] = num;
	}

	for(int i = 0; i < TamanioVector; i++){
		float num = ((float)rand()/(float)(RAND_MAX) * a);
		Vector2[i] = num;
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