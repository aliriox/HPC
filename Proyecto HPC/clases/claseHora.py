from clases.claseMateria import *
class Hora():
    def __init__(self, m, g):
        self.materia = m
        self.grados = g

    def get_nombreMateria_Hora(self):
        return self.materia.get_nombreMateria()
    def get_intensidad_Hora(self, indiceGrado):
        intensidad = self.materia.get_intensidad()
        return intensidad[indiceGrado]
