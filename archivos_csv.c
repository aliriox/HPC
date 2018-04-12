#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]){
	
	FILE *fp;
	fp = fopen("entradaM1.csv", "r");
	
	if(fp == NULL){
		printf("archivo no encontrado");
		return 1;
	}
	
	char cadena[100];
	fscanf(fp, "%s", cadena);
	printf("%s", cadena);
	fclose(fp);
	
	printf("\n");
	
	// metodo para separar los datos con ;
	
	char *tok = strtok(cadena, ";");

	int i = 1;
	
	do{
		printf("%s\n",tok);
		i++;
		tok = strtok(NULL, ";");
	}while(tok != NULL);
	
	sprintf("El numero de columnas es: %d\n", i);
	
	printf("\n");
	
	/* metodo de transformacion string a float
		
	float a;
	
	a = strtod(tok , NULL);
	printf("%f", a);
	
	*/
	return 0;
	
}
