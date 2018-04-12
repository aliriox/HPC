#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 10000

int Detected_rows(FILE *fp, char nombre[]){

	fp = fopen(nombre,"r");

	int i = 0;
	char c[N];
	while(fscanf(fp,"%s",c) != EOF){
		i++;
	}
	fclose(fp);
	return i;
}

int Detected_columns(FILE *fp, char nombre[100]){

	fp = fopen(nombre, "r");
	char cadena[N];
	fscanf(fp,"%s",cadena);

	char *tok = strtok(cadena, ";");
	int i = 0;
	do{
		i++;
		tok = strtok(NULL, ";");
	}while(tok != NULL);
	fclose(fp);

	return i;
}

int main(int argc, char *argv[]){

	char nombre[N] = "entrada1omp.csv";
	
	FILE *fp;
	fp = fopen(nombre, "r");
	
	if(fp == NULL){
		printf("archivo no encontrado");
		return 1;
	}
	fclose(fp);

	int rows_1 = Detected_rows(fp,nombre);
	printf("El numero de filas es: %d\n", rows_1);

	int columns_1 = Detected_columns(fp,nombre);
	printf("El numero de columnas es: %d\n", columns_1);
	
	/* metodo de transformacion string a float
		
	float a;
	
	a = strtod(tok , NULL);
	printf("%f", a);
	
	*/
	return 0;
	
}
