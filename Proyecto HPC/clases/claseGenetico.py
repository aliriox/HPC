from pymongo import MongoClient
from datetime import datetime
from clases.conectorBD import *
import random

def reproduccion(padre,madre):
	hijo=padre
	for i in ["Lunes","Martes","Miercoles","Jueves","Viernes"]:
		for j in range (0,6):
			gen_padre = padre[i][j]
			gen_madre = madre[i][j]
			if(gen_madre == gen_padre):
				gen_hijo = gen_madre
			else:
				gen = random.randint(0,1)
				if (gen == 0):
					hijo[i][j] = gen_padre
				else: 
					hijo[i][j] = gen_madre
	return hijo

def evaluador(horario,grado,indiceGrado):
	calificacion=0
	materias = obtenerIntensidades(grado)

	for k in materias:
		del k['_id']
		del k['Grados']
		NombreAsignatura = k['NombreMateria']
		intensidad = k['Intensidades'][indiceGrado]
		contador=0
		bandera=0
		for i in ["Lunes","Martes","Miercoles","Jueves","Viernes"]:
			contador=horario[i].count(NombreAsignatura) +  contador
		if(contador != intensidad):
			bandera=1
		else:
			bandera=0
	if(bandera==1):
		calificacion = calificacion - 60
	else:
		calificacion = calificacion + 40
	for i in ["Lunes","Martes","Miercoles","Jueves","Viernes"]:
		for j in range (0,6):
			Elemento = horario[i][j]
			conteo = horario[i].count(Elemento)
			if(conteo <= 2):
				calificacion = calificacion + 2
			else:
				calificacion = calificacion - 8
	return calificacion


def crearPoblacion(grado,generacionActual,indiceGrado):
	tamano= conteoRegistros(generacionActual,grado)
	for i in range (0,int(tamano/2)):
		padre = random.randint(0,tamano-1)
		madre = random.randint(0,tamano-1)
		horarioPadre = obtenerHorario(generacionActual,grado,padre)
		horarioMadre = obtenerHorario(generacionActual,grado,madre)
		del horarioPadre['_id']
		del horarioPadre['Grado']
		del horarioMadre['_id']
		del horarioMadre['Grado']
		horarioHijo = reproduccion(horarioPadre,horarioMadre)
		calificacion_Padre = evaluador(horarioPadre,grado,indiceGrado)
		calificacion_Madre = evaluador(horarioMadre,grado,indiceGrado)
		calificacion_Hijo = evaluador(horarioHijo,grado,indiceGrado)
		if(calificacion_Madre >= calificacion_Padre):
			if(calificacion_Madre >= calificacion_Hijo):
				NuevaGeneracion = horarioMadre
			else:
				NuevaGeneracion = horarioHijo
		else:
			if(calificacion_Padre >= calificacion_Hijo):
				NuevaGeneracion = horarioPadre
			else:
				NuevaGeneracion = horarioHijo
		insertarHorarioGeneracion(generacionActual,grado, NuevaGeneracion['Lunes'], NuevaGeneracion['Martes'], NuevaGeneracion['Miercoles'], NuevaGeneracion['Jueves'], NuevaGeneracion['Viernes'])


