from clases.claseHora import *
from clases.claseMateria import *
from clases.conectorBD import *
from algoritmoGenetico import *
import random

'''
Funcion Generar Materias:
    Argumentos = ninguno.
    Entradas = documento separado por comas extencion csv.
    Salidas = lista de materias con sus respectivas intensidades.
    Restricciones = Asegurarse de que la carpeta entradas exista.
                    Asegurarse de que el archivo entradas.csv exista.
                    Evitar espacios en blanco (EJ: ;;).
                    Evite que el archivo entradas.csv este vacio.
    Descripcion =   Esta funcion crea una lista de materias con su respectiva
                    intensidad horaria por grado de forma matricial, usando
                    el archivo csv en la carpeta entradas.
'''
def generarMaterias():
    #Abrir archivo de entradas.csv.
    entrada = open("entradas/entradas.csv",'r')
    #Leer todo el contenido del documento.
    lectura = entrada.read()
    #Separa por lineas el documento y las almacena en una lista de strings.
    lecturaMaterias = lectura.split("\n")
    #Elimina la primera fila que almacena los grados.
    nombreGrados = lecturaMaterias[0].split(";")
    del nombreGrados[0]
    del lecturaMaterias[0]
    #Crea la lista de materias vacia.
    materias = []
    #Ciclo para leer cada materia junto a su intesidad por grado.
    for i in lecturaMaterias:
        #Separa el nombre de la materia y la intensidad por grado en una lista.
        conjuntoMateriaIntensidad = i.split(";")
        #El nombre de la materia siempre esta en la posicion 0 de la lista.
        nombreMateria = conjuntoMateriaIntensidad[0]
        #Crea una nueva variable para almacenar las intensidades.
        intensidadGrados = conjuntoMateriaIntensidad
        '''
        Alternativa: Es posible ahorrarse costos en memoria y tiempo si
                    el delete se realiza directamente sobre la variable
                    conjuntoMateriaIntensidad.
        '''
        #Elimina la primera posicion que almacena el nombre de la materia.
        del intensidadGrados[0]
        #Usa la clase materia y crea una nueva materia con sus intensidades.
        materia = Materia(nombreMateria,intensidadGrados)
        #Agrega a la lista de materia la nueva materia.
        materias.append(materia)
    #retorna la lista de Materias
    materias.pop()
    for i in materias:
        insertarIntensidades(i.get_nombreMateria(), nombreGrados, i.get_intensidadesMateria())
    return materias

'''
Funcion Generar Tokens:
    Argumentos = indiceGrado: almacena la posicion en la que esta la intesidad
                 de una materia segun su grado.
                 materias: Recibe la lista de materias.
    Entradas = Ninguna.
    Salidas = Retorna una lista de tokens que almacena horas de clase por
              materias (EJ: mate=2, esp=1=>[mate,mate,esp]).
    Restricciones = Asegurarse de que no existan intensidades negativas
                    intensidad > 0.
    Descripcion =   Esta funcion genera una lista de tokens que almacena las
                    horas de estudio a la semana de una materia para cada salon,
                    normalmente es una lista de 30 posiciones.
'''
def generarTokens(indiceGrado, materias):
    #Crea una lista de tokens vacia.
    tokens = []
    #Realiza un ciclo por cada maria en la lista de materias.
    for i in materias:
        #Captura la intensidad semanal de la materia en cada ciclo, la convierte
        #en un entero.
        #print(i.get_intensidadesMateria())
        cantidadHorasSemanal = int(i.get_intensidadGrado(indiceGrado))
        #Si la cantidad de horas a la semana es positiva y mayor que 0.
        if(cantidadHorasSemanal > 0):
            #Hace un ciclo de 0 a la intensidad semanal
            for j in range (0 , cantidadHorasSemanal):
                #crea una hora de clase por cada hora de la intensidad semanal
                token = Hora(i,indiceGrado)
                #agrega el token creado a la lista de tokens
                tokens.append(token)
    #retorna la lista de tokens
    return tokens

'''
Funcion Imprimir Dia:
    Argumentos = dia: una lista con el horario del dia.
    Entradas = Ninguna.
    Salidas = Ninguna.
    Restricciones = Ninguna.
    Descripcion = Esta funcion imprime en pantalla el horario de un dia.
'''
def imprimirDia(dia):
    #Para cada elemnto de la lista de dia
    for i in dia:
        #Imprime el nombre de la materia de cada hora.
        print(i.get_nombreMateria_Hora())

'''
Funcion Generar Dia:
    Argumentos = Tokens: una lista que contiene las posibles horas que puede ver
                 un grupo.
    Entradas = Ninguna.
    Salidas = Retorna una lista con las horas de un dia para un grupo.
    Restricciones = Asegurarse de que nToken nunca sea mayor a la cantidad de
                    tokens que hay en la lista de tokens.
    Descripcion = Esta funcion toma de forma aleatorea una hora de la lista de
                  tokens y genera horario para un dia.
'''
def generarDia(tokens):
    #Escoge un numero de 0 al tamano de la lista de tokens de forma aleatorea.
    nToken = random.randint(0,len(tokens)-1)
    #Crea un vector vacio en el que se almacenaran las horas del dia.
    horas = []
    #crea un contador que controla el numero maximo de horas por dia.
    cont = 0
    #ciclo que no supera las 6 horas diarias.
    while (cont < 6):
        #Almacena la hora escogida en la variable hora.
        hora = tokens[nToken]
        #Agrega la hora a la lista de horas.
        horas.append(hora.get_nombreMateria_Hora())
        #Elimina la hora de la lista de tokens.
        del tokens[nToken]
        #Solo elige nToken mientras que la lista de tokens tenga mas de 1 elemnto.
        if(len(tokens)>1):
            nToken = random.randint(0,len(tokens)-1)
        else:
            nToken = 0
        #Incrementa el contador en 1.
        cont = cont + 1
    #Retorna la lista de horas de un dia.
    return horas

'''
Funcion Generar Horario:
    Argumentos = grado: recibe el grado al que se le va a generar el horario.
                 materias: recibe la lista con los nombres de las materias.
                 indiceGrado: recibe el indice del grado seleccionado.
    Entradas = ninguno.
    Salidas = crea un archivo para cada grado con su horario con el formato de
              'grado'.csv.
    Restricciones = Asegurarse de que la carpeta 'salidas' exista.
                    Evite tener archivos con el mismo nobre.
    Descripcion = Esta funcion genera el horario para todos los grados de la
                  lista de grados.
'''
def generarHorario(grado, materias, indiceGrado):
    tokens = generarTokens(indiceGrado, materias)
    horarioSemana = []
    for i in range(0,5):
        dia = generarDia(tokens)
        horarioSemana.append(dia)
    insertarHorarioGrado( grado,horarioSemana[0], horarioSemana[1],horarioSemana[2], horarioSemana[3],horarioSemana[4])


def lecturaGrados():
    entrada = open("entradas/entradas.csv",'r')
    grados = entrada.readline()
    vectorGrados = grados.split("\n")
    vectorGrados.pop()
    auxGrados = vectorGrados[0].split(";")

    auxGrados.remove("grados")
    while('' in auxGrados):
            auxGrados.remove('')
    entrada.close()
    return auxGrados

def main():
    grados = lecturaGrados()
    materias = generarMaterias()
    for i in grados:
        for j in range (0,500):
            generarHorario(i,materias, grados.index(i))
        print("Fue generado los horarios iniciales para grado: " + i)
    receptorGenetico(grados)

    print("█▀▀ █  █ █  █ ▀▀█▀▀ █   █ █▀▀▄")
    print("▀▀█ █▀▀█ █  █   █   █   █ █  █")
    print("▀▀▀ ▀  ▀ ▀▀▀▀   ▀    ▀▀▀  █▀▀")
    print("▄▀▀▄ █▀▀▄ █▀▀▄ ")
    print("█▄▄█ █  █ █  █ ")
    print("█  █ █  █ █▄▄▀")
    print("")
    print("     ███    ██")
    print("      ████   ███")
    print("        ████  ███")
    print("         ████ █████")
    print("████████  █████████")
    print("████████████████████")
    print("████████████████████")
    print("█████████████████████")
    print("█████████████████████")
    print("█████████████████████")
    print("██     ██████████████")
    print("███        █████████")
    print("█  █           ████")
    print("█              ██")
    print("██              █        ▄███████▄")
    print("██   ███▄▄  ▄▄███      ▄██$█████$██▄")
    print("██  █▀   ▀███    █   ▄██$█████████$██▄")
    print("██  █   █  ██   █ █  █$█████████████$█")
    print("██  █      ██     █  █████████████████")
    print("██  ██    ██▀█   █    ██████████████")
    print(" █   ██████  ▀████      ███████████")
    print("                  █      █████████")
    print("             ▀▀████     ███████████")
    print("                █▀      ██  ████▀ ▀█")
    print("                ▀█     █     ▀█▀   █")
    print("  ▄▄▄▄▄▄▄        ██   █   ████▀   ██")
    print(" █████████████    ▀█  █   ███▀  ▄▄██")
    print(" █▀██▀██▀████▀█████▀  █   ██████▀ ▀█")
    print(" █        █▄         ██   ████▀   ██")
    print(" ██▄████▄  ██        ██   ██  ▄▄▄██")
    print("  ██▄▄▄▄▄██▀         ██  █████▀   █")
    print("         ███         ███████▄   ███")
    print("        ███████     █████████████")
    print("       ▄██████████████████████")
    print("████████ ██████████████████")
    print("         ██████████████")
    print("        ███████████")
    print("       █████")
    print("      ████")
    print("     ████")
    print("")
    print("▀▀█▀▀ █▀▀█ █ ▄█  █▀▀ ")
    print("  █   █▄▄█ █▀▀▄  █▀▀ ")
    print("  ▀   ▀  ▀ ▀  ▀  ▀▀▀ ")
    print("")
    print("█▀▄▀█ █  █   █▀▄▀█ ▄▀▀▄ █▀▀▄ █▀▀ █  █ █ ")
    print("█ ▀ █ █▄▄█   █ ▀ █ █  █ █  █ █▀▀ █▄▄█ █")
    print("█   █ ▄▄▄█   █   █  ▀▀  ▀  ▀ ▀▀▀ ▄▄▄█ ▄")
main()