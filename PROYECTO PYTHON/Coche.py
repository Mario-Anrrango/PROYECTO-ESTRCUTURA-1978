from datetime import datetime
from typing import List, Optional
from ValidacionPlaca import Placa
from Validaciones import Validaciones
from Menu import menu_interactivo
from Propietario import Propietario


class Coche:
    def __init__(self, placa="", modelo="", color="", marca="", anio=0, hora_ingreso=None, hora_salida=None):
        if hora_ingreso is None:
            hora_ingreso = datetime.now()
        self.placa = placa
        self.modelo = modelo
        self.color = color
        self.marca = marca
        self.anio = anio
        self.hora_ingreso = hora_ingreso
        self.hora_salida = hora_salida

    def set_hora_salida(self, hora: datetime):
        self.hora_salida = hora

    def set_placa(self, placa: str):
        self.placa = placa

    def set_modelo(self, modelo: str):
        self.modelo = modelo

    def set_marca(self, marca: str):
        self.marca = marca

    def set_color(self, color: str):
        self.color = color

    def get_hora_salida(self) -> Optional[datetime]:
        return self.hora_salida

    def get_placa(self) -> str:
        return self.placa

    def get_marca(self) -> str:
        return self.marca

    def get_modelo(self) -> str:
        return self.modelo

    def get_color(self) -> str:
        return self.color

    def get_anio(self) -> int:
        return self.anio

    def get_hora_ingreso(self) -> datetime:
        return self.hora_ingreso

    def __str__(self) -> str:
        hora_ingreso = self.hora_ingreso.strftime('%Y-%m-%d %H:%M:%S')
        hora_salida = self.hora_salida.strftime('%Y-%m-%d %H:%M:%S') if self.hora_salida else "N/A"
        return f"Placa: {self.placa}\nMarca: {self.marca}\nModelo: {self.modelo}\nColor: {self.color}\n" \
               f"Hora de Ingreso: {hora_ingreso}\nHora de Salida: {hora_salida}\n"

    def insertar_datos(self, lista, lista_historial, lista_propietarios):
        validaciones = Validaciones()
        validador = Placa()

        placa = ""
        modelo = ""
        color = ""
        marca = ""
        cedula = ""
        anio = 0

        propietario_nodo = None
        propietario_encontrado = False

        while not propietario_encontrado:
            cedula = validaciones.ingresar_cedula("Ingrese el numero de cedula del propietario: ")
            propietario_nodo = lista_propietarios.get_primero()

            while propietario_nodo:
                if propietario_nodo.dato.get_cedula() == cedula:
                    propietario_encontrado = True
                    break
                propietario_nodo = propietario_nodo.get_siguiente()

            if not propietario_encontrado:
                print("No se encontro un propietario con esa cedula. Por favor, intente de nuevo.")

        while True:
            placa = validador.ingresar_placa(lista.get_primero())

            temp = lista.get_primero()
            placa_duplicada = False

            while temp:
                coche_actual = temp.dato
                if coche_actual.get_placa() == placa and coche_actual.get_hora_salida() is None:
                    print(f"\nEl coche con la placa {placa} ya está en el parqueadero. Ingrese una placa nueva.")
                    placa_duplicada = True
                    break
                temp = temp.get_siguiente()

            if not placa_duplicada:
                break

        temp_historial = lista_historial.get_primero()
        if temp_historial:
            while temp_historial:
                coche_historial = temp_historial.dato
                if coche_historial.get_placa() == placa:
                    print(f"\nLa placa {placa} fue encontrada en el historial. Recuperando datos...")
                    modelo = coche_historial.get_modelo()
                    color = coche_historial.get_color()
                    marca = coche_historial.get_marca()

                    print(f"Marca: {marca}\nColor: {color}\nModelo: {modelo}\n")

                    opciones = ["Si", "No"]
                    seleccion = menu_interactivo(opciones, "Auto encontrado en el sistema.\n¿Desea sobreescribir los datos del historial?")

                    if seleccion == 0:  # Si
                        print("========================================")
                        print("        Datos Recuperados Exitosamente  ")
                        print("========================================")
                        print(f"\nMarca:    {marca}")
                        print(f"Modelo:   {modelo}")
                        print(f"Color:    {color}")
                        print(f"Placa:    {placa}")

                        propietario_actualizado = Propietario(
                            propietario_nodo.dato.get_nombre(),
                            propietario_nodo.dato.get_apellido(),
                            propietario_nodo.dato.get_cedula(),
                            propietario_nodo.dato.get_correo(),
                            propietario_nodo.dato.get_placas()
                        )
                        propietario_actualizado.agregar_placa(placa)
                        propietario_nodo.set_dato(propietario_actualizado)

                        lista_propietarios.guardar_propietarios("propietarios.txt")

                        return Coche(placa, modelo, color, marca, anio)

                    else:  # No
                        print("\nPor favor, ingrese los datos manualmente:")
                        break

                temp_historial = temp_historial.get_siguiente()

        marca = validaciones.ingresar_string("Ingrese la marca: ")
        color = validaciones.ingresar_string("Ingrese el color: ")
        modelo = validaciones.ingresar_string("Ingrese el modelo: ")

        propietario_actualizado = Propietario(
            propietario_nodo.dato.get_nombre(),
            propietario_nodo.dato.get_apellido(),
            propietario_nodo.dato.get_cedula(),
            propietario_nodo.dato.get_correo(),
            propietario_nodo.dato.get_placas()
        )
        propietario_actualizado.agregar_placa(placa)

        propietario_nodo.set_dato(propietario_actualizado)

        lista_propietarios.guardar_propietarios("propietarios.txt")

        return Coche(placa, modelo, color, marca, anio)

# Aquí pueden ir las implementaciones de las clases Validaciones, Placa, ListaCircularDoble, Propietario y las funciones necesarias.
