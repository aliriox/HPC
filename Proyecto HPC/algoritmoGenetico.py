#BEGIN /* Algoritmo Genetico Simple */
#	Generar una poblacion inicial.
#	Computar la funcion de evaluacion de cada individuo
#	WHILE NOT Terminado DO
#	BEGIN /* Producir nueva generacion */
#		FOR Taman˜o poblacion/2 DO 
#		BEGIN /*Ciclo Reproductivo *
#			Seleccionar dos individuos de la anterior generacion, para el cruce (probabilidad de seleccion proporcional a la funcion de evaluacion del individuo).
#			Cruzar con cierta probabilidad los dos individuos obteniendo dos descendientes.
#			Mutar los dos descendientes con cierta probabilidad
#			Computar la funcion de evaluacion de los dos descendientes mutados.
#			Insertar los dos descendientes mutados en la nueva generacion.
#		END
#		IF la poblacion ha convergido THEN 
#			Terminado := TRUE
#	END
#END
from clases.claseGenetico import *

def controlProfesores():
	entrada = open("entradas/profesores.csv",'r')
	profesores = entrada.readline()
	vectorProfesores = profesores.split("\n")
	nombreAsignaturas = vectorProfesores[0].split(";")
	del nombreAsignaturas[0]
	del vectorProfesores[0]

	docentes = []
	vectorProfesores.pop()
	for i in VectorProfesores:
		auxProfesores = i.split(";")
		while('' in auxProfesores):
			auxProfesores.remove('')
		nombreProfesores = i[0]
	entrada.close()


def receptorGenetico(listaGrados):
	grados=[]
	grados = listaGrados
	inicializador(grados)

def inicializador(grados):
	print("iniciando el Algoritmo")
	generacion = ["1_generacion","2_generacion","3_generacion","4_generacion","5_generacion"]
	indiceGrado=0
	for i in grados:
		print("Algoritmo para el Grado: " + i)
		indiceGrado = indiceGrado + 1
		for j in generacion: 
			crearPoblacion(i,j,indiceGrado)
			print("la " + j + " a sido añadida para el grado: " + i)

	#controlProfesores()