# main.py
from Menu import menu 
from ListaCircularDoble import ListaCircularDoble
from Estacionamiento import Estacionamiento
from Parqueadero import Parqueadero
from ArbolAvl import ArbolAvl

def main():
    listaPropietarios = ListaCircularDoble()
    arbolCoches = ArbolAvl()

    listaPropietarios.CargarPropietarios("propietarios.txt")

    listaCochesHistorial = ListaCircularDoble()
    listaCochesHistorial.CargarArchivo("autos_historial.txt")

    estacionamiento = Estacionamiento()

    listaCoches = ListaCircularDoble()
    listaCoches.CargarArchivo("autos.txt")

    parqueadero = Parqueadero()

    # Llama a la función cargar_menu que maneja las importaciones
    menu(listaCoches, listaCochesHistorial, listaPropietarios, estacionamiento, parqueadero, arbolCoches)

if __name__ == "__main__":
    main()
