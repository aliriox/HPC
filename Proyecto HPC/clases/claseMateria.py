class Materia():
    def __init__(self, nM, iG):
        self.nombreMateria = nM
        self.intensidad = iG

    def get_nombreMateria(self):
        return self.nombreMateria
    def get_intensidad(self):
        return self.intensidad
    def get_intensidadesMateria(self):
        intensidades=[]
        for i in self.intensidad:
            if (i==""):
                horas = 0
            else:
                horas= int(i)
            intensidades.append(horas)
        return intensidades
    def get_intensidadGrado(self,indiceGrado):

    	intensidad = self.intensidad[indiceGrado]

    	if((intensidad == "")):
    		return 0
    	else:
    		return intensidad
