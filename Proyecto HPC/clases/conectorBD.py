from pymongo import MongoClient
from datetime import datetime

client = MongoClient()

def insertarHorarioGrado(grado, lunes, martes, miercoles, jueves, viernes):
	#Es seguro estar conectando la bd cada vez que se realice una consulta, pero no es optimo en procesamiento
	db = client.Horarios
	result = db.jornada.insert_one(
		{
		"Grado" : grado,
		"Lunes" : lunes,
		"Martes" : martes,
		"Miercoles" : miercoles,
		"Jueves" : jueves,
		"Viernes" : viernes
		}
	)
	result.inserted_id
	
def insertarProfesor(nombreProfesor, materias):
	db = client.Horarios
	result = db.profesores.insert_one(
		{
		"NombreProfesor" : nombreProfesor,
		"materias" : materias
		})
	resul.inserted_id

def insertarIntensidades(nombreMateria,grados,intensidades):
	#Es seguro estar conectando la bd cada vez que se realice una consulta, pero no es optimo en procesamiento
	db = client.Horarios
	result = db.intensidades.insert_one(
		{
		"NombreMateria" : nombreMateria,
		"Grados" : grados,
		"Intensidades" : intensidades
		}
	)
	result.inserted_id

def obtenerHorariosGrado(grado):
	#Es seguro estar conectando la bd cada vez que se realice una consulta, pero no es optimo en procesamiento
	db = client.Horarios
	result = db.intensidades.find(
		{
		"Grados" : grados
		}
	)
	result.inserted_id

def conteoRegistros(generacionActual,grado):
	db = client.Horarios
	if(generacionActual == "1_generacion"):		
		result = db.jornada.count({"Grado":grado})
	if(generacionActual == "2_generacion"):		
		result = db.generacion_1.count({"Grado":grado})
	if(generacionActual == "3_generacion"):		
		result = db.generacion_2.count({"Grado":grado})
	if(generacionActual == "4_generacion"):		
		result = db.generacion_3.count({"Grado":grado})
	if(generacionActual == "5_generacion"):		
		result = db.generacion_4.count({"Grado":grado})
	if(generacionActual == "Final"):
		result = db.generacion_5.count({"Grado":grado})
	return result

def insertarHorarioGeneracion(generacionActual,grado, lunes, martes, miercoles, jueves, viernes):
	db = client.Horarios
	if(generacionActual == "1_generacion"):		
		result = db.generacion_1.insert_one(
		{
		"Grado" : grado,
		"Lunes" : lunes,
		"Martes" : martes,
		"Miercoles" : miercoles,
		"Jueves" : jueves,
		"Viernes" : viernes
		})
	if(generacionActual == "2_generacion"):		
		result = db.generacion_2.insert_one(
		{
		"Grado" : grado,
		"Lunes" : lunes,
		"Martes" : martes,
		"Miercoles" : miercoles,
		"Jueves" : jueves,
		"Viernes" : viernes
		})
	if(generacionActual == "3_generacion"):		
		result = db.generacion_3.insert_one(
		{
		"Grado" : grado,
		"Lunes" : lunes,
		"Martes" : martes,
		"Miercoles" : miercoles,
		"Jueves" : jueves,
		"Viernes" : viernes
		})
	if(generacionActual == "4_generacion"):		
		result = db.generacion_4.insert_one(
		{
		"Grado" : grado,
		"Lunes" : lunes,
		"Martes" : martes,
		"Miercoles" : miercoles,
		"Jueves" : jueves,
		"Viernes" : viernes
		})
	if(generacionActual == "5_generacion"):		
		result = db.generacion_5.insert_one(
		{
		"Grado" : grado,
		"Lunes" : lunes,
		"Martes" : martes,
		"Miercoles" : miercoles,
		"Jueves" : jueves,
		"Viernes" : viernes
		})
	result.inserted_id

def obtenerHorario(generacionActual,grado,numeroLlave):
	db = client.Horarios
	if(generacionActual == "1_generacion"):
		result = db.jornada.find({"Grado":grado}).limit(-1).skip(numeroLlave).next()
	if(generacionActual == "2_generacion"):		
		result = db.generacion_1.find({"Grado":grado}).limit(-1).skip(numeroLlave).next()
	if(generacionActual == "3_generacion"):		
		result = db.generacion_2.find({"Grado":grado}).limit(-1).skip(numeroLlave).next()
	if(generacionActual == "4_generacion"):		
		result = db.generacion_3.find({"Grado":grado}).limit(-1).skip(numeroLlave).next()
	if(generacionActual == "5_generacion"):		
		result = db.generacion_4.find({"Grado":grado}).limit(-1).skip(numeroLlave).next()
	if(generacionActual == "Final"):		
		result = db.generacion_5.find({"Grado":grado}).limit(-1).skip(numeroLlave).next()
	return result

def obtenerIntensidades(grado):
	db = client.Horarios
	result = db.intensidades.find({"Grados" : grado})
	return result