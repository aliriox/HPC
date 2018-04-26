#include <stdlib.h>
#include <stdio.h>
#include <gtk/gtk.h>

int main( int argc, char *argv[] )
{
    /* Inicializa los widgets que se van a utilizar (inicialmente la ventana)*/
    GtkWidget *ventana;

    /* Arranca GTK+ */
    gtk_init (&argc, &argv);

    /* Define los tipos de widget y los configura*/
    // creamos la ventana
    ventana = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // con esto terminamos la ejecucion al  cerrar la ventana
    g_signal_connect(G_OBJECT(ventana),"destroy", gtk_main_quit, NULL);

    // ponemos título a la ventana
	gtk_window_set_title(GTK_WINDOW(ventana), "Tabla Grafica");

    //Dimensionar la ventana
	gtk_window_set_default_size(GTK_WINDOW(ventana), 800, 600);

    // mostramos la ventana
    gtk_widget_show (ventana);

    /* Arranca el programa*/
    gtk_main ();

    /* Finaliza el programa*/
      return 0;
}