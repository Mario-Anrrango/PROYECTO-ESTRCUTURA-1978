import random
from Estacionamiento import Estacionamiento
from ArbolAvl import ArbolAvl

class Parqueadero:
    def __init__(self):
        self.estacionamiento = Estacionamiento()  # Usando la clase Estacionamiento definida previamente
        self.arbol_coches = ArbolAvl()  # Usando la clase ArbolAVL definida previamente
        self.TAMANIO = 100

    def agregar_coche(self, coche):
        espacio_libre = self.estacionamiento.obtener_espacio_aleatorio()  # Obtener espacio aleatorio

        # Ocupa el espacio con el coche
        self.estacionamiento.ocupar_espacio(espacio_libre, coche)

        # Agrega la distancia al árbol de coches
        self.arbol_coches.agregar_distancia(espacio_libre)

    def mostrar_estado_parqueadero(self):
        print("Estado del Parqueadero:")
        self.estacionamiento.mostrar_estacionamiento()

    def mostrar_coches(self):
        print("Coches estacionados:")
        self.arbol_coches.mostrar_distancias()

    def cargar_y_asignar_parqueadero(self, lista_coches, arbol_coches):
        self.estacionamiento.vaciar_estacionamiento()  # Vaciar el estacionamiento
        arbol_coches.vaciar_arbol()  # Vaciar el árbol de coches

        if not lista_coches:
            print("La lista de coches está vacía.")
            return

        for coche in lista_coches:
            posicion_aleatoria = self.estacionamiento.obtener_espacio_aleatorio()  # Obtener espacio aleatorio
            self.estacionamiento.ocupar_espacio(posicion_aleatoria, coche)  # Asignar coche al espacio
            arbol_coches.agregar_distancia(posicion_aleatoria)  # Agregar la distancia al árbol

    def inicializar_semilla(self):
        random.seed(0)  # Inicializa la semilla aleatoria
