#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void EscribirArchivo(float **Matriz,char nombre[], int TamanioMatriz){

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

	int TamanioMatriz;
	float ** Matriz1;
	float ** Matriz2;
	float ** Resultado;

	printf("Ingrese el tamanio del vector: \n");
	scanf("%d",&TamanioMatriz);

	Matriz1 = (float**) malloc (TamanioMatriz*sizeof(float*));
	Matriz2 =  (float**) malloc (TamanioMatriz*sizeof(float*));
	Resultado = (float**) malloc (TamanioMatriz*sizeof(float*));

	if(Matriz1 == NULL || Matriz2 == NULL){
		printf("error reservando memoria malloc");
		exit(1);
	}

	for(int i = 0; i < TamanioMatriz; i++){
		Matriz1[i] = (float*) malloc (TamanioMatriz*sizeof(float));
		Matriz2[i] = (float*) malloc (TamanioMatriz*sizeof(float));
		Resultado[i] = (float*) malloc (TamanioMatriz*sizeof(float));
	}

	
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
	
	

	EscribirArchivo(Matriz1,"entradaM1.csv", TamanioMatriz);
	EscribirArchivo(Matriz2,"entradaM2.csv", TamanioMatriz);

	

	for (int i = 0;i < TamanioMatriz; i++){
		for (int j = 0;j < TamanioMatriz; j++){
			Resultado[i][j]=0;
         	for (int k = 0;k < TamanioMatriz; k++){
         		Resultado[i][j] = Resultado[i][j] + Matriz1[i][k] * Matriz2[k][j];
          	}
       	}
    }


	
	EscribirArchivo(Resultado,"resultadoM.csv", TamanioMatriz);
	

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