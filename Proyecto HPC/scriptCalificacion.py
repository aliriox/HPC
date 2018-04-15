from clases.claseHora import *
from clases.claseMateria import *
from clases.conectorBD import *
from algoritmoGenetico import *
import random
archivo = open("puntajes.csv",'w')
grados = ["6","7","8","9","10","11","1","2","3","4","5"]
generaciones= ["2_generacion","3_generacion","4_generacion","5_generacion","Final"]
for k in generaciones:
	print(k)
	exitoGeneracion=0
	contadorGeneracion=0
	archivo.write("Generacion: "+ k +"\n")
	for i in grados:
		exitoGrado=0
		contadorGrado=0
		archivo.write("Grado: " + i +"\n")
		tamano= conteoRegistros(k,i)
		for j in range (0,tamano-1):
			horario=obtenerHorario(k,i,j)
			evalHorario = evaluador(horario,i,grados.index(i))
			if(evalHorario>=80):
				contadorGrado=contadorGrado+1
		exitoGrado=(contadorGrado/tamano)
		#archivo.write("en el grado -" + i + "- el porcentaje de exito fue del: " + str(exitoGrado) +"%\n")
		archivo.write(str(exitoGrado) +"\n")
		contadorGeneracion=contadorGeneracion+exitoGrado
	exitoGeneracion= (contadorGeneracion/len(grados))
	archivo.write("Total generacional\n" )
archivo.close()
		