import os
import keyboard
import sys
import msvcrt 
from datetime import datetime
import time
from Validaciones import Validaciones
from Propietario import Propietario
from NodoAvl import NodoAvl
from Ordenamiento import ordenar_lista, ordenar_lista_bucket, ordenar_lista_bubble_sort, ordenar_lista_shell_sort, ordenar_lista_por_radix


class menu:

    def __init__(self, lista, lista_historial, lista_propietarios, estacionamiento, parqueadero, arbol_coches):
        self.lista = lista
        self.lista_historial = lista_historial
        self.lista_propietarios = lista_propietarios
        self.estacionamiento = estacionamiento
        self.parqueadero = parqueadero
        self.arbol_coches = arbol_coches
        self.validaciones = Validaciones()


        
def menu_eliminar_placa(lista_propietarios):
    validaciones = Validaciones()
    os.system('cls' if os.name == 'nt' else 'clear')
    print("========================================")
    print("========================================")
    print("    ELIMINAR PLACA DE PROPIETARIO       ")
    print("========================================")
    print("========================================")

    cedula = validaciones.ingresar_cedula("Ingrese la cedula del propietario: ")
    aux = lista_propietarios.get_primero()
    encontrado = False

    while True:
        if aux.get_dato().get_cedula() == cedula:
            encontrado = True
            print("========================================")
            print("   PROPIETARIO REGISTRADO")
            print("========================================")
            print(aux.get_dato())

            placas = aux.get_dato().get_placas()

            if not placas:
                print("Este propietario no tiene placas asociadas.")
                return

            opciones_placas = placas.copy()
            opciones_placas.append("Volver")
            seleccion = menu_interactivo(opciones_placas, "Seleccionar Placa a Eliminar")

            if seleccion == len(opciones_placas) - 1:
                return

            placa = placas[seleccion]

            placas_actualizadas = aux.get_dato().eliminar_placa(placa)

            propietario_actualizado = Propietario(
                aux.get_dato().get_nombre(),
                aux.get_dato().get_apellido(),
                aux.get_dato().get_cedula(),
                aux.get_dato().get_correo()
            )
            propietario_actualizado.set_placas(placas_actualizadas)

            aux.set_dato(propietario_actualizado)
            print(aux.get_dato())

            lista_propietarios.guardar_propietarios("propietarios.txt")

            break

        aux = aux.get_siguiente()
        if aux == lista_propietarios.get_primero():
            break

    if not encontrado:
        print("No se encontró un propietario con esa cédula.")


def menu_interactivo(opciones, titulo):
    seleccion = 0
    num_opciones = len(opciones)

    while True:
        os.system('cls')

        print("========================================")
        print("========================================")
        print(f"        {titulo}")
        print("========================================")
        print("========================================")

        for i, opcion in enumerate(opciones):
            if i == seleccion:
                print(f" > {opcion} < ")
            else:
                print(f"   {opcion}")

        print("========================================")

        # Esperar a que el usuario presione una tecla
        tecla = msvcrt.getch()

        if tecla == b'\xe0':  # Tecla especial (flechas)
            tecla = msvcrt.getch()
            if tecla == b'H':  # Flecha arriba
                seleccion = (seleccion - 1 + num_opciones) % num_opciones
            elif tecla == b'P':  # Flecha abajo
                seleccion = (seleccion + 1) % num_opciones
        elif tecla == b'\r':  # Enter
            return seleccion
            


def menu_gestion_propietarios(lista_propietarios):
    salir_submenu = False
    while not salir_submenu:
        os.system('cls' if os.name == 'nt' else 'clear')
        print("========================================")
        print("========================================")
        print("      Menu de Gestion de Propietarios   ")
        print("========================================")
        print("========================================")

        opciones_propietarios = [
            "Agregar Propietario",
            "Mostrar Propietarios",
            "Busqueda Avanzada",
            "Eliminar Placa de Propietario",
            "Volver al Menu Principal"
        ]

        seleccion_propietarios = menu_interactivo(opciones_propietarios, "Menu de Gestion de Propietarios")

        if seleccion_propietarios == 0:
            nuevo_propietario = Propietario.agregar_propietario()
            lista_propietarios.insertar(nuevo_propietario)
            lista_propietarios.guardar_propietarios("propietarios.txt")
        elif seleccion_propietarios == 1:
            lista_propietarios.mostrar(lista_propietarios.get_primero())
            input("Presione Enter para continuar...")
        elif seleccion_propietarios == 2:
            os.system('cls' if os.name == 'nt' else 'clear')
            print("========================================")
            print("          BUSQUEDA AVANZADA             ")
            print("========================================")
            menu_busqueda_avanzada_propietario(lista_propietarios)
            input("Presione Enter para continuar...")
        elif seleccion_propietarios == 3:
            menu_eliminar_placa(lista_propietarios)
        elif seleccion_propietarios == 4:
            salir_submenu = True
        else:
            print("Opción no válida. Intente de nuevo.")


def menu_busqueda_avanzada_propietario(lista_propietarios):
    validaciones = Validaciones()
    opciones_busqueda = [
        "Buscar por Cedula",
        "Buscar por Correo",
        "Buscar por Nombre",
        "Buscar por Apellido",
        "Volver al Menu Principal"
    ]

    while True:
        seleccion_busqueda = menu_interactivo(opciones_busqueda, "Menu de Busqueda Avanzada")

        if seleccion_busqueda == 0:
            os.system('cls' if os.name == 'nt' else 'clear')
            print("========================================")
            print("  Buscar por Cedula")
            print("========================================")
            cedula = validaciones.ingresar_cedula("Ingrese la cedula: ")
            lista_propietarios.busqueda_avanzada_propietario("cedula", cedula, "")
        elif seleccion_busqueda == 1:
            os.system('cls' if os.name == 'nt' else 'clear')
            print("========================================")
            print("  Buscar por Correo")
            print("========================================")
            correo = validaciones.ingresar_correo("Ingrese el correo: ")
            lista_propietarios.busqueda_avanzada_propietario("correo", correo, "")
        elif seleccion_busqueda == 2:
            os.system('cls' if os.name == 'nt' else 'clear')
            print("========================================")
            print("  Buscar por Nombre")
            print("========================================")
            nombre = validaciones.ingresar_string("Ingrese el nombre: ")
            lista_propietarios.busqueda_avanzada_propietario("nombre", nombre, "")
        elif seleccion_busqueda == 3:
            os.system('cls' if os.name == 'nt' else 'clear')
            print("========================================")
            print("  Buscar por Apellido")
            print("========================================")
            apellido = validaciones.ingresar_string("Ingrese el apellido: ")
            lista_propietarios.busqueda_avanzada_propietario("apellido", apellido, "")
        elif seleccion_busqueda == 4:
            print("Saliendo...")
            return
        else:
            print("Opción inválida. Inténtelo de nuevo.")

        input("Presione Enter para continuar...")


def menu(lista, lista_historial, lista_propietarios, estacionamiento, parqueadero, arbol_coches):

    
    from ListaCircularDoble import ListaCircularDoble  # Importa cuando se necesita
    from Coche import Coche  # Importa cuando se necesita
    
    validaciones = Validaciones()
    parqueadero.inicializar_semilla()
    parqueadero.cargar_y_asignar_parqueadero(lista, arbol_coches)

    opciones = [
        "Insertar Coche",
        "Mostrar Lista de Coches",
        "Busqueda de Coche Por Placa",
        "Busqueda Avanzada",
        "Menu de Gestion de Propietarios",
        "Liberar el parqueadero",
        "Ordenar Lista",
        "Ayuda",
        "Mostrar Arbol AVL",
        "Salir"
    ]

    archivo = "autos.txt"
    archivo_historial = "autos_historial.txt"

    while True:
        seleccion = menu_interactivo(opciones, "Menu de Parqueadero")

        if seleccion == 0:
            if lista_propietarios.esta_vacia():
                print("No hay propietarios registrados. Por favor, registre un propietario antes de continuar.")
                continue

            nuevo_coche = Coche.insertar_datos(lista, lista_historial, lista_propietarios)
            lista.insertar(nuevo_coche)
            lista.guardar_archivo(archivo)
            lista_historial.insertar(nuevo_coche)
            lista_historial.guardar_archivo(archivo_historial)
            parqueadero.agregar_coche(nuevo_coche)
            espacio = estacionamiento.obtener_espacio_aleatorio()
            estacionamiento.ocupar_espacio(espacio, nuevo_coche)
            parqueadero.mostrar_estado_parqueadero()

        elif seleccion == 1:
            salir_submenu = False
            while not salir_submenu:
                os.system('cls' if os.name == 'nt' else 'clear')
                print("========================================")
                print("========================================")
                print("         Menu de Lista de Coches        ")
                print("========================================")
                print("========================================")

                opciones_lista = [
                    "Mostrar Coches en Parqueadero",
                    "Mostrar Historial Completo de Coches",
                    "Volver al Menu Principal"
                ]

                seleccion_lista = menu_interactivo(opciones_lista, "Menu de Lista de Coches")

                if seleccion_lista == 0:
                    os.system('cls' if os.name == 'nt' else 'clear')
                    print("========================================")
                    print("   LISTA DE COCHES EN EL PARQUEADERO    ")
                    print("========================================")
                    lista.mostrar()
                    input("Presione Enter para continuar...")
                elif seleccion_lista == 1:
                    os.system('cls' if os.name == 'nt' else 'clear')
                    print("========================================")
                    print("   HISTORIAL COMPLETO DE COCHES         ")
                    print("========================================")
                    lista_historial.mostrar()
                    input("Presione Enter para continuar...")
                elif seleccion_lista == 2:
                    print("Regresando al menu principal...")
                    salir_submenu = True
                else:
                    print("Opción inválida. Inténtelo de nuevo.")
                    input("Presione Enter para continuar...")

        elif seleccion == 2:
            salir_submenu = False
            while not salir_submenu:
                os.system('cls' if os.name == 'nt' else 'clear')
                print("========================================")
                print("========================================")
                print("        Menu de Busqueda por Placa      ")
                print("========================================")
                print("========================================")

                opciones_busqueda = [
                    "Buscar en Parqueadero",
                    "Buscar en Historial",
                    "Volver al Menu Principal"
                ]

                seleccion_busqueda = menu_interactivo(opciones_busqueda, "Menu de Busqueda por Placa")

                if seleccion_busqueda == 0:
                    os.system('cls' if os.name == 'nt' else 'clear')
                    print("========================================")
                    print("   BUSQUEDA DE PLACA EN PARQUEADERO     ")
                    print("========================================")
                    placa = input("Ingrese la placa a buscar (Utilice mayúsculas para validar su placa): ")
                    lista.buscar_por_placa(placa)
                    input("Presione Enter para continuar...")
                elif seleccion_busqueda == 1:
                    os.system('cls' if os.name == 'nt' else 'clear')
                    print("========================================")
                    print("   BUSQUEDA DE PLACA EN HISTORIAL       ")
                    print("========================================")
                    placa = input("Ingrese la placa a buscar (Utilice mayúsculas para validar su placa): ")
                    lista_historial.buscar_por_placa(placa)
                    input("Presione Enter para continuar...")
                elif seleccion_busqueda == 2:
                    print("Regresando al menu principal...")
                    salir_submenu = True
                else:
                    print("Opción inválida. Inténtelo de nuevo.")
                    input("Presione Enter para continuar...")

        elif seleccion == 3:
            os.system('cls' if os.name == 'nt' else 'clear')
            print("========================================")
            print("========================================")
            print("     BIENVENIDOS A LA BUSQUEDA AVANZADA  ")
            print("========================================")
            print("========================================")
            menu_busqueda_avanzada(lista, lista_historial)

        elif seleccion == 4:
            menu_gestion_propietarios(lista_propietarios)

        elif seleccion == 5:
            os.system('cls' if os.name == 'nt' else 'clear')
            print("========================================")
            print("========================================")
            print("  BIENVENIDOS A LA GESTION DE ESTACIONAMIENTO ")
            print("========================================")
            print("========================================")
            placa = input("Ingrese la placa del coche que va a dejar el estacionamiento: ")
            lista_historial.salir_del_parqueadero(placa)
            lista.eliminar_por_placa(placa)
            parqueadero.inicializar_semilla()
            parqueadero.cargar_y_asignar_parqueadero(lista, arbol_coches)
            parqueadero.mostrar_estado_parqueadero()

        elif seleccion == 6:
            menu_ordenar(lista, lista_historial, lista_propietarios)

        elif seleccion == 7:
            os.system('cls' if os.name == 'nt' else 'clear')
            print("========================================")
            print("========================================")
            print("               (i)AYUDA                 ")
            print("========================================")
            print("========================================")
            archivo = "ayuda.html"
            if os.name == 'nt':
                os.system(f"start {archivo}")
            else:
                os.system(f"xdg-open {archivo}")

        elif seleccion == 8:
            os.system('cls' if os.name == 'nt' else 'clear')
            print("========================================")
            print("========================================")
            print("          MOSTRAR ARBOL                 ")
            print("========================================")
            print("========================================")
            arbol_coches.mostrar_arbol()

        elif seleccion == 9:
            print("Saliendo...")
            return
        else:
            print("Opción inválida. Inténtelo de nuevo.")

        input("Presione Enter para continuar...")

            
import os

def menu_busqueda_avanzada(lista, lista_historial):
    validaciones = Validaciones()
    opciones = [
        "Buscar en Parqueadero",
        "Buscar en Historial de Coches",
        "Volver al Menu Principal"
    ]

    while True:
        seleccion = menu_interactivo(opciones, "Menu de Busqueda Avanzada")

        if seleccion == 0:
            opciones_busqueda = [
                "Buscar por Modelo",
                "Buscar por Color",
                "Buscar por Año/Fecha",
                "Buscar por Marca",
                "Buscar por Hora",
                "Volver al Menu Principal"
            ]

            seleccion_busqueda = menu_interactivo(opciones_busqueda, "Menu de Busqueda en Parqueadero")

            if seleccion_busqueda == 0:
                os.system("cls")
                print("========================================")
                print("  Buscar por Modelo")
                print("========================================")
                modelo = validaciones.ingresar_string("Ingrese el modelo: ")
                lista.busqueda_avanzada("modelo", modelo, "")
            elif seleccion_busqueda == 1:
                os.system("cls")
                print("========================================")
                print("  Buscar por Color")
                print("========================================")
                color = validaciones.ingresar_string("Ingrese el color: ")
                lista.busqueda_avanzada("color", color, "")
            elif seleccion_busqueda == 2:
                os.system("cls")
                print("========================================")
                print("  Buscar por Año/Fecha")
                print("========================================")
                fecha = input("Ingrese la fecha (DD-MM-AAAA): ")
                lista.busqueda_avanzada("fecha", fecha, "")
            elif seleccion_busqueda == 3:
                os.system("cls")
                print("========================================")
                print("  Buscar por Marca")
                print("========================================")
                marca = validaciones.ingresar_string("Ingrese la marca: ")
                lista.busqueda_avanzada("marca", marca, "")
            elif seleccion_busqueda == 4:
                os.system("cls")
                print("========================================")
                print("  Buscar por Hora")
                print("========================================")
                hora_entrada1 = input("Ingrese la hora de entrada 1: ")
                hora_entrada2 = input("Ingrese la hora de entrada 2: ")
                lista.busqueda_avanzada("hora", hora_entrada1, hora_entrada2)
            elif seleccion_busqueda == 5:
                print("Saliendo...")
                return
            else:
                print("Opción inválida. Inténtalo de nuevo.")

        elif seleccion == 1:
            opciones_busqueda = [
                "Buscar por Modelo",
                "Buscar por Color",
                "Buscar por Año/Fecha",
                "Buscar por Marca",
                "Buscar por Hora",
                "Volver al Menu Principal"
            ]

            seleccion_busqueda = menu_interactivo(opciones_busqueda, "Menu de Busqueda en Historial")

            if seleccion_busqueda == 0:
                os.system("cls")
                print("========================================")
                print("  Buscar por Modelo")
                print("========================================")
                modelo = validaciones.ingresar_string("Ingrese el modelo: ")
                lista_historial.busqueda_avanzada("modelo", modelo, "")
            elif seleccion_busqueda == 1:
                os.system("cls")
                print("========================================")
                print("  Buscar por Color")
                print("========================================")
                color = validaciones.ingresar_string("Ingrese el color: ")
                lista_historial.busqueda_avanzada("color", color, "")
            elif seleccion_busqueda == 2:
                os.system("cls")
                print("========================================")
                print("  Buscar por Año/Fecha")
                print("========================================")
                fecha = input("Ingrese la fecha (DD-MM-AAAA): ")
                lista_historial.busqueda_avanzada("fecha", fecha, "")
            elif seleccion_busqueda == 3:
                os.system("cls")
                print("========================================")
                print("  Buscar por Marca")
                print("========================================")
                marca = validaciones.ingresar_string("Ingrese la marca: ")
                lista_historial.busqueda_avanzada("marca", marca, "")
            elif seleccion_busqueda == 4:
                os.system("cls")
                print("========================================")
                print("  Buscar por Hora")
                print("========================================")
                hora_entrada1 = input("Ingrese la hora de entrada 1: ")
                hora_entrada2 = input("Ingrese la hora de entrada 2: ")
                lista_historial.busqueda_avanzada("hora", hora_entrada1, hora_entrada2)
            elif seleccion_busqueda == 5:
                print("Saliendo...")
                return
            else:
                print("Opción inválida. Inténtalo de nuevo.")

        elif seleccion == 2:
            print("Saliendo...")
            return
        else:
            print("Opción inválida. Inténtalo de nuevo.")

        os.system("pause")

def menu_ordenar_coches(lista, lista_historial):
    salir_submenu = False

    while not salir_submenu:
        os.system("cls")
        print("========================================")
        print("           Menu de Ordenamiento de Coches         ")
        print("========================================")

        opciones_metodo = [
            "Quick Sort",
            "Bucket Sort",
            "Bubble Sort",
            "Shell Sort",
            "Radix sort",
            "Volver al Menu Principal"
        ]

        seleccion_metodo = menu_interactivo(opciones_metodo, "Seleccione el metodo de ordenamiento:")

        if seleccion_metodo == 5:
            salir_submenu = True
            continue

        opciones_ordenar = [
            "Ordenar por Placa",
            "Ordenar por Color",
            "Ordenar por Modelo",
            "Ordenar por Marca",
            "Volver al Menu Principal"
        ]

        seleccion_ordenar = menu_interactivo(opciones_ordenar, "Seleccione el criterio de ordenamiento:")

        if seleccion_ordenar == 4:
            continue

        os.system("cls")
        if seleccion_metodo == 0:
            if seleccion_ordenar == 0:
                ordenar_lista(lista, lambda a, b: a.get_placa() < b.get_placa())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por placa y guardada exitosamente.")
            elif seleccion_ordenar == 1:
                ordenar_lista(lista, lambda a, b: a.get_color() < b.get_color())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por color y guardada exitosamente.")
            elif seleccion_ordenar == 2:
                ordenar_lista(lista, lambda a, b: a.get_modelo() < b.get_modelo())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por modelo y guardada exitosamente.")
            elif seleccion_ordenar == 3:
                ordenar_lista(lista, lambda a, b: a.get_marca() < b.get_marca())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por marca y guardada exitosamente.")
            else:
                print("Opción inválida. Intente de nuevo.")
        elif seleccion_metodo == 1:
            if seleccion_ordenar == 0:
                get_key_coche = lambda item: item.get_placa()
                ordenar_lista_bucket(lista, get_key_coche)
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por placa y guardada exitosamente.")
            elif seleccion_ordenar == 1:
                get_key_coche = lambda item: item.get_color()
                ordenar_lista_bucket(lista, get_key_coche)
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por color y guardada exitosamente.")
            elif seleccion_ordenar == 2:
                get_key_coche = lambda item: item.get_modelo()
                ordenar_lista_bucket(lista, get_key_coche)
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por modelo y guardada exitosamente.")
            elif seleccion_ordenar == 3:
                get_key_coche = lambda item: item.get_marca()
                ordenar_lista_bucket(lista, get_key_coche)
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por marca y guardada exitosamente.")
            else:
                print("Opción inválida. Intente de nuevo.")
        elif seleccion_metodo == 2:
            if seleccion_ordenar == 0:
                ordenar_lista_bubble_sort(lista, lambda a, b: a.get_placa() < b.get_placa())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por placa y guardada exitosamente.")
            elif seleccion_ordenar == 1:
                ordenar_lista_bubble_sort(lista, lambda a, b: a.get_color() < b.get_color())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por color y guardada exitosamente.")
            elif seleccion_ordenar == 2:
                ordenar_lista_bubble_sort(lista, lambda a, b: a.get_modelo() < b.get_modelo())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por modelo y guardada exitosamente.")
            elif seleccion_ordenar == 3:
                ordenar_lista_bubble_sort(lista, lambda a, b: a.get_marca() < b.get_marca())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por marca y guardada exitosamente.")
            else:
                print("Opción inválida. Intente de nuevo.")
        elif seleccion_metodo == 3:
            if seleccion_ordenar == 0:
                ordenar_lista_shell_sort(lista, lambda a, b: a.get_placa() < b.get_placa())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por placa y guardada exitosamente.")
            elif seleccion_ordenar == 1:
                ordenar_lista_shell_sort(lista, lambda a, b: a.get_color() < b.get_color())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por color y guardada exitosamente.")
            elif seleccion_ordenar == 2:
                ordenar_lista_shell_sort(lista, lambda a, b: a.get_modelo() < b.get_modelo())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por modelo y guardada exitosamente.")
            elif seleccion_ordenar == 3:
                ordenar_lista_shell_sort(lista, lambda a, b: a.get_marca() < b.get_marca())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por marca y guardada exitosamente.")
            else:
                print("Opción inválida. Intente de nuevo.")
        elif seleccion_metodo == 4:
            if seleccion_ordenar == 0:
                ordenar_lista_por_radix(lista, lambda coche: coche.get_placa())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por placa y guardada exitosamente.")
            elif seleccion_ordenar == 1:
                ordenar_lista_por_radix(lista, lambda coche: coche.get_color())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por color y guardada exitosamente.")
            elif seleccion_ordenar == 2:
                ordenar_lista_por_radix(lista, lambda coche: coche.get_modelo())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por modelo y guardada exitosamente.")
            elif seleccion_ordenar == 3:
                ordenar_lista_por_radix(lista, lambda coche: coche.get_marca())
                lista.guardar_archivo("autos.txt")
                print("Lista ordenada por marca y guardada exitosamente.")
            else:
                print("Opción inválida. Intente de nuevo.")

        os.system("pause")

def menu_ordenar_propietarios(lista_propietarios):
    salir_submenu = False

    while not salir_submenu:
        os.system("cls")
        print("========================================")
        print("           Menu de Ordenamiento de Propietarios         ")
        print("========================================")

        opciones_metodo = [
            "Quick Sort",
            "Bucket Sort",
            "Bubble Sort",
            "Shell Sort",
            "Radix sort",
            "Volver al Menu Principal"
        ]

        seleccion_metodo = menu_interactivo(opciones_metodo, "Seleccione el metodo de ordenamiento:")

        if seleccion_metodo == 5:
            salir_submenu = True
            continue

        opciones_ordenar = [
            "Ordenar por Nombre",
            "Ordenar por Apellido",
            "Ordenar por Cedula",
            "Ordenar por Correo",
            "Volver al Menu Principal"
        ]

        seleccion_ordenar = menu_interactivo(opciones_ordenar, "Seleccione el criterio de ordenamiento:")

        if seleccion_ordenar == 4:
            continue

        os.system("cls")
        if seleccion_metodo == 0:
            if seleccion_ordenar == 0:
                ordenar_lista(lista_propietarios, lambda a, b: a.get_nombre() < b.get_nombre())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por nombre y guardada exitosamente.")
            elif seleccion_ordenar == 1:
                ordenar_lista(lista_propietarios, lambda a, b: a.get_apellido() < b.get_apellido())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por apellido y guardada exitosamente.")
            elif seleccion_ordenar == 2:
                ordenar_lista(lista_propietarios, lambda a, b: a.get_cedula() < b.get_cedula())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por cedula y guardada exitosamente.")
            elif seleccion_ordenar == 3:
                ordenar_lista(lista_propietarios, lambda a, b: a.get_correo() < b.get_correo())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por correo y guardada exitosamente.")
            else:
                print("Opción inválida. Intente de nuevo.")
        elif seleccion_metodo == 1:
            if seleccion_ordenar == 0:
                get_key_propietario = lambda item: item.get_nombre()
                ordenar_lista_bucket(lista_propietarios, get_key_propietario)
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por nombre y guardada exitosamente.")
            elif seleccion_ordenar == 1:
                get_key_propietario = lambda item: item.get_apellido()
                ordenar_lista_bucket(lista_propietarios, get_key_propietario)
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por apellido y guardada exitosamente.")
            elif seleccion_ordenar == 2:
                get_key_propietario = lambda item: item.get_cedula()
                ordenar_lista_bucket(lista_propietarios, get_key_propietario)
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por cedula y guardada exitosamente.")
            elif seleccion_ordenar == 3:
                get_key_propietario = lambda item: item.get_correo()
                ordenar_lista_bucket(lista_propietarios, get_key_propietario)
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por correo y guardada exitosamente.")
            else:
                print("Opción inválida. Intente de nuevo.")
        elif seleccion_metodo == 2:
            if seleccion_ordenar == 0:
                ordenar_lista_bubble_sort(lista_propietarios, lambda a, b: a.get_nombre() < b.get_nombre())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por nombre y guardada exitosamente.")
            elif seleccion_ordenar == 1:
                ordenar_lista_bubble_sort(lista_propietarios, lambda a, b: a.get_apellido() < b.get_apellido())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por apellido y guardada exitosamente.")
            elif seleccion_ordenar == 2:
                ordenar_lista_bubble_sort(lista_propietarios, lambda a, b: a.get_cedula() < b.get_cedula())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por cedula y guardada exitosamente.")
            elif seleccion_ordenar == 3:
                ordenar_lista_bubble_sort(lista_propietarios, lambda a, b: a.get_correo() < b.get_correo())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por correo y guardada exitosamente.")
            else:
                print("Opción inválida. Intente de nuevo.")
        elif seleccion_metodo == 3:
            if seleccion_ordenar == 0:
                ordenar_lista_shell_sort(lista_propietarios, lambda a, b: a.get_nombre() < b.get_nombre())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por nombre y guardada exitosamente.")
            elif seleccion_ordenar == 1:
                ordenar_lista_shell_sort(lista_propietarios, lambda a, b: a.get_apellido() < b.get_apellido())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por apellido y guardada exitosamente.")
            elif seleccion_ordenar == 2:
                ordenar_lista_shell_sort(lista_propietarios, lambda a, b: a.get_cedula() < b.get_cedula())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por cedula y guardada exitosamente.")
            elif seleccion_ordenar == 3:
                ordenar_lista_shell_sort(lista_propietarios, lambda a, b: a.get_correo() < b.get_correo())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por correo y guardada exitosamente.")
            else:
                print("Opción inválida. Intente de nuevo.")
        elif seleccion_metodo == 4:
            if seleccion_ordenar == 0:
                ordenar_lista_por_radix(lista_propietarios, lambda propietario: propietario.get_nombre())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por nombre y guardada exitosamente.")
            elif seleccion_ordenar == 1:
                ordenar_lista_por_radix(lista_propietarios, lambda propietario: propietario.get_apellido())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por apellido y guardada exitosamente.")
            elif seleccion_ordenar == 2:
                ordenar_lista_por_radix(lista_propietarios, lambda propietario: propietario.get_cedula())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por cedula y guardada exitosamente.")
            elif seleccion_ordenar == 3:
                ordenar_lista_por_radix(lista_propietarios, lambda propietario: propietario.get_correo())
                lista_propietarios.guardar_propietarios("propietarios.txt")
                print("Lista ordenada por correo y guardada exitosamente.")
            else:
                print("Opción inválida. Intente de nuevo.")

        os.system("pause")

def menu_ordenar(lista, lista_historial, lista_propietarios):
    salir_menu = False

    while not salir_menu:
        os.system("cls")
        print("========================================")
        print("           Menu de Ordenamiento         ")
        print("========================================")

        opciones_tipo = [
            "Ordenar por Coche",
            "Ordenar por Propietario",
            "Volver al Menu Principal"
        ]

        seleccion_tipo = menu_interactivo(opciones_tipo, "Seleccione el tipo de ordenamiento:")

        if seleccion_tipo == 2:
            salir_menu = True
            continue

        if seleccion_tipo == 0:
            menu_ordenar_coches(lista, lista_historial)
        elif seleccion_tipo == 1:
            menu_ordenar_propietarios(lista_propietarios)