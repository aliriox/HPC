#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define INT_LEN (10)
#define HEX_LEN (8)
#define BIN_LEN (32)
#define OCT_LEN (11)

char *  itoa ( int value, char * str, int base )
{
    int i,n =2,tmp;
    char buf[BIN_LEN+1];


    switch(base)
    {
        case 16:
            for(i = 0;i<HEX_LEN;++i)
            {
                if(value/base>0)
                {
                    n++;
                }
            }
            snprintf(str, n, "%x" ,value);
            break;
        case 10:
            for(i = 0;i<INT_LEN;++i)
            {
                if(value/base>0)
                {
                    n++;
                }
            }
            snprintf(str, n, "%d" ,value);
            break;
        case 8:
            for(i = 0;i<OCT_LEN;++i)
            {
                if(value/base>0)
                {
                    n++;
                }
            }
            snprintf(str, n, "%o" ,value);
            break;
        case 2:
            for(i = 0,tmp = value;i<BIN_LEN;++i)
            {
                if(tmp/base>0)
                {
                    n++;
                }
                tmp/=base;
            }
            for(i = 1 ,tmp = value; i<n;++i)
            {
                if(tmp%2 != 0)
                {
                    buf[n-i-1] ='1';
                }
                else
                {
                    buf[n-i-1] ='0';
                }
                tmp/=base;
            }
            buf[n-1] = '\0';
            strcpy(str,buf);
            break;
        default:
            return NULL;
    }
    return str;
}

int main(){

	int n = 34;

    unsigned char *f;
    f = "1,2,3";
    unsigned char *tmp;
    tmp = "4,5,6";
    char *pr = "7";

    unsigned char *c = (char *)malloc(1000*sizeof(char*));
    strcat(c,f);
    strcat(c,",");
    strcat(c,tmp);
    strcat(c,",");
    strcat(c,pr);
    char *a;

    a = c;
    //itoa(n,a,10); 
    printf("%s\n", a);

    /*
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
    */
    free(c);
}