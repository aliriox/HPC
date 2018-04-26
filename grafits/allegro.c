#include <stdio.h> 
#include <stdlib.h> 
#include <allegro5/allegro.h> // Librería inicial de Allegro 
#include <allegro5/allegro_primitives.h> // Addon de primitivas (figuras)

#define VENTANA_X 800 
#define VENTANA_Y 600
#define NEGRO al_map_rgb(0,0,0)
#define BLANCO al_map_rgb(255,255,255)
#define AZUL al_map_rgb(0,0,255) 
#define VERDE al_map_rgb(0,255,0)
#define ROJO al_map_rgb(255,0,0)
#define N 2
#define M 600

// Redefinición de tipos 
typedef ALLEGRO_DISPLAY aDisplay; 

// Variables globales 
aDisplay *dis = NULL; 

// Funciones 
void inicializar(void){ 
    // Inicializar los addons 
    if(!al_init()) 
    { 
        fprintf(stderr, "Error al inicializar Allegro."); // Imprimir errores en stream STDERR
        exit(-1); 
    } 
    if(!al_init_primitives_addon()) 
    { 
        fprintf(stderr, "Error al inicializar el addon de primitivas."); // Imprimir errores en stream STDERR
        exit(-2); 
    } 

    dis = al_create_display(VENTANA_X, VENTANA_Y); // Crear el display de tamaño 500x300 píxeles

    al_set_window_title(dis, "Tabla Grafica"); // Establecer el título de la ventana
}

void finalizar(){ 
    al_shutdown_primitives_addon(); // Finalizar el addon de primitivas
    al_destroy_display(dis); // Destruir la ventana 
}

void colorearPantalla(){ 
    al_clear_to_color(BLANCO); // Limpiar la ventana y establecer un color de fondo RGB (color rojo: R=0=0.0, G=255=1.0, B=0=0.0)
}

void Puntos(int *v){
    for(int i = 0; i < M*N; i++){
        al_draw_filled_circle(v[i]+10, VENTANA_Y-v[i+M]-10, 1.0, ROJO); // Crear un círculo: x = 200px, y = 160px, radio = 130px, color
    }
}

void tabla(){
    // linea y
    float x1 = 10.0;
    float x2 = 10.0;
    float y1 = 0;
    float y2 = VENTANA_Y;
    al_draw_line(x1,y1,x2,y2,NEGRO,2);
    // linea x
    float X1 = 0;
    float Y1 = VENTANA_Y - 10.0;
    float X2 = VENTANA_X;
    float Y2 = Y1;
    al_draw_line(X1,Y1,X2,Y2,NEGRO,2);

    //subdivisiones de la grafica
    int division = 10;
    int Tam_Y = VENTANA_Y - 20;
    int Tam_X = VENTANA_X - 20;

    int incre = Tam_Y / division;

    for(int i = 10; i <= VENTANA_Y; i += incre){
        al_draw_line(x1-3, i,x2+3, i,NEGRO,1);
    }

    incre = Tam_X / division;

    for(int i = 10; i <= VENTANA_X; i += incre){
        al_draw_line(i ,Y1-3, i, Y1+3,NEGRO,1);
    }

}

void Graficar(int *v){
    inicializar(); 
    colorearPantalla();
    tabla();
    Puntos(v);
    al_flip_display(); // Dibujar en pantalla todo lo almacenado en el buffer, en este caso solamente está el círculo de arriba
    getchar(); // cerrar ventana despues de pulsar una tecla (enfoque-->terminal)
    finalizar(); 
} 

int main(){
    
    int *vector = (int*)malloc(N*M*sizeof(int));

    for(int i = 0; i < N; i++){
        for(int j = 0; j < M; j++){
            bool tmp = true;
            while(tmp){
                int num = rand() %  (M-20) + 1;
                if(num <= 580){
                    vector[i * M + j] = num;
                    tmp = false;
                }
            }
            //printf("vector[%d] = %d\n", i * M + j,vector[i*M+j]);
            //vector[i*M+j] = i*M+j+10;
        }
    }
    Graficar(vector);
    free(vector);
    return 0; 
} 