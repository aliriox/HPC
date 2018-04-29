#include <stdlib.h>
#include <stdio.h>

int main(){

	int n = 3;
	int Matriz1[n][n];
	int Matriz2[n][n];


	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			Matriz1[i][j] = rand()%10;
			Matriz2[i][j] = rand()%10;
		}
	}

	int MatrizRespuesta[n][n];

	for (int i = 0;i < n; i++){
		for (int j = 0;j < n; j++){
			MatrizRespuesta[i][j]=0;
         	for (int k = 0;k < n; k++){
         		MatrizRespuesta[i][j]=MatrizRespuesta[i][j]+Matriz1[i][k]*Matriz2[k][j];
          	}
       	}
    }

    for(int i = 0; i < n; i++){
    	for(int j = 0; j < n; j++){
    		printf("[%d]", Matriz1[i][j]);
    	}
    	printf("\n");
    }

    printf("\n");

    for(int i = 0; i < n; i++){
    	for(int j = 0; j < n; j++){
    		printf("[%d]", Matriz2[i][j]);
    	}
    	printf("\n");
    }

    printf("\n");

    for(int i = 0; i < n; i++){
    	for(int j = 0; j < n; j++){
    		printf("[%d]", MatrizRespuesta[i][j]);
    	}
    	printf("\n");
    }

	return 0;
}