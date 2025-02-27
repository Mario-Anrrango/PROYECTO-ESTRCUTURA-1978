from Nodo import Nodo
from Coche import Coche as T
from Propietario import Propietario as T
import datetime


class ListaCircularDoble:
    def __init__(self):
        self.Primero = None
        self.Ultimo = None

    def set_primero(self, Primero):
        self.Primero = Primero

    def get_primero(self):
        return self.Primero

    def set_ultimo(self, Ultimo):
        self.Ultimo = Ultimo

    def get_ultimo(self):
        return self.Ultimo

    def __iter__(self):
        # Método para que se pueda iterar sobre la lista circular doble
        if self.Primero is None:
            return

        nodo_actual = self.Primero
        while True:
            yield nodo_actual.dato
            nodo_actual = nodo_actual.siguiente
            if nodo_actual == self.Primero:  # Si volvemos al Primero, terminamos la iteración
                break

    def insertar(self, dato):
        nuevo_carro = Nodo(dato)

        if self.Primero is None:
            self.Primero = nuevo_carro
            self.Primero.set_siguiente(self.Primero)
            self.Primero.set_anterior(self.Primero)
            self.Ultimo = self.Primero
        else:
            self.Ultimo.set_siguiente(nuevo_carro)
            nuevo_carro.set_anterior(self.Ultimo)
            self.Ultimo = nuevo_carro
            self.Ultimo.set_siguiente(self.Primero)
            self.Primero.set_anterior(self.Ultimo)

    def buscar_por_placa(self, placa):
        if self.Primero is None:
            print("La lista está vacía.")
            return

        aux = self.Primero
        while True:
            if aux.get_dato().get_placa() == placa:
                print("========================================")
                print("   AUTOMOVIL REGISTRADO")
                print("========================================")
                print(aux.get_dato())
                return
            aux = aux.siguiente
            if aux == self.Primero:
                break

        print(f"El coche con la placa {placa} no está en el parqueadero.")

    def mostrar(self):
        if self.Primero is None:
            print("La lista está vacía.")
            return

        aux = self.Primero
        print("========================================")
        print("   LISTA DE COCHES EN EL PARQUEADERO    ")
        print("========================================")
        print(aux.get_dato())

        aux = aux.siguiente
        while aux != self.Primero:
            print(aux.get_dato())
            aux = aux.siguiente

    def eliminar_por_placa(self, placa):
        if self.Primero is None:
            print("La lista está vacía.")
            return

        aux = self.Primero
        anterior = None
        hora_eliminacion = datetime.now()

        if self.Primero == self.Ultimo and self.Primero.get_dato().get_placa() == placa:
            del self.Primero
            self.Primero = None
            self.Ultimo = None
            print(f"El coche con la placa {placa} ha sido eliminado.")
            return

        while True:
            if aux.get_dato().get_placa() == placa:
                if aux == self.Primero:
                    self.Primero = self.Primero.siguiente
                    self.Primero.set_anterior(self.Ultimo)
                    self.Ultimo.set_siguiente(self.Primero)
                elif aux == self.Ultimo:
                    self.Ultimo = self.Ultimo.anterior
                    self.Ultimo.set_siguiente(self.Primero)
                    self.Primero.set_anterior(self.Ultimo)
                else:
                    anterior = aux.anterior
                    anterior.set_siguiente(aux.siguiente)
                    aux.siguiente.set_anterior(anterior)

                del aux
                print(f"El coche con la placa {placa} ha sido eliminado.")
                return

            aux = aux.siguiente
            if aux == self.Primero:
                break

        print(f"El coche con la placa {placa} no se encontró en el parqueadero.")


    def busqueda_avanzada(self, criterio, valor_inicio, valor_fin=None):
        if self.Primero is None:
            print("La lista está vacía.")
            return

        encontrado = False
        aux = self.Primero
        valor_inicio = valor_inicio.lower()

        while True:
            if criterio == "marca":
                marca = aux.get_dato().get_marca().lower()
                if marca == valor_inicio:
                    print("========================================")
                    print("   AUTOMOVIL REGISTRADO POR MARCA")
                    print("========================================")
                    print(aux.get_dato())
                    encontrado = True
            elif criterio == "modelo":
                modelo = aux.get_dato().get_modelo().lower()
                if modelo == valor_inicio:
                    print("========================================")
                    print("   AUTOMOVIL REGISTRADO POR MODELO")
                    print("========================================")
                    print(aux.get_dato())
                    encontrado = True
            elif criterio == "color":
                color = aux.get_dato().get_color().lower()
                if color == valor_inicio:
                    print("========================================")
                    print("   AUTOMOVIL REGISTRADO POR COLOR")
                    print("========================================")
                    print(aux.get_dato())
                    encontrado = True
            elif criterio == "hora":
                hora_ingreso = aux.get_dato().get_hora()
                hora_actual = hora_ingreso.strftime("%H:%M:%S")
                if valor_inicio <= hora_actual <= valor_fin:
                    print("========================================")
                    print("   AUTOMOVIL REGISTRADO POR HORA")
                    print("========================================")
                    print(aux.get_dato())
                    encontrado = True

            aux = aux.siguiente
            if aux == self.Primero:
                break

        if not encontrado:
            print(f"No se encontró ningún automóvil con el criterio de búsqueda: {criterio}")
         

    def CargarArchivo(self, nombre_archivo):
        try:
            with open(nombre_archivo, 'r') as archivo:
                for linea in archivo:
                    datos = linea.strip().split(',')
                    if len(datos) == 6:
                        placa, modelo, color, marca, fecha_ingreso, hora_salida = datos
                        
                        placa = self.descifrar_texto(placa)

                        # Convertir fecha de ingreso
                        try:
                            fecha_ingreso_parsed = datetime.datetime.strptime(fecha_ingreso, "%a %b %d %H:%M:%S %Y")
                        except ValueError:
                            print(f"Error en el formato de la fecha de ingreso: {fecha_ingreso}")
                            continue
                        
                        # Convertir hora de salida
                        if hora_salida == "N/A" or not hora_salida:
                            hora_salida_parsed = None
                        else:
                            try:
                                hora_salida_parsed = datetime.datetime.strptime(hora_salida, "%a %b %d %H:%M:%S %Y")
                            except ValueError:
                                print(f"Error en el formato de la hora de salida: {hora_salida}")
                                hora_salida_parsed = None

                        coche = T(placa, modelo, color, marca, fecha_ingreso_parsed, hora_salida_parsed)
                        self.insertar(coche)

        except FileNotFoundError:
            print(f"Error: No se pudo abrir el archivo {nombre_archivo}. Creando archivo vacío...")
            try:
                with open(nombre_archivo, 'w') as nuevo_archivo:
                    pass
            except Exception as e:
                print(f"Error: No se pudo crear el archivo {nombre_archivo}: {str(e)}")

    def guardar_archivo(self, nombre_archivo):
        try:
            with open(nombre_archivo, 'w') as archivo:
                print("Abriendo archivo para guardar los datos...")
                actual = self.Primero
                if actual is None:
                    return

                while True:
                    coche = actual.dato
                    placa_cifrada = self.cifrar_texto(coche.placa)
                    hora_ingreso = coche.hora_ingreso
                    hora_ingreso_time = hora_ingreso.timestamp()
                    hora_ingreso_str = datetime.fromtimestamp(hora_ingreso_time).strftime("%a %b %d %H:%M:%S %Y")

                    if coche.hora_salida is not None:
                        hora_salida_time = coche.hora_salida.timestamp()
                        hora_salida_str = datetime.fromtimestamp(hora_salida_time).strftime("%a %b %d %H:%M:%S %Y")
                    else:
                        hora_salida_str = "N/A"
                    
                    archivo.write(f"{placa_cifrada},{coche.modelo},{coche.color},{coche.marca},{hora_ingreso_str},{hora_salida_str}\n")
                    actual = actual.siguiente
                    if actual == self.Primero:
                        break
        except IOError:
            print(f"Error: No se pudo abrir el archivo {nombre_archivo}. Creando archivo nuevo...")
            try:
                with open(nombre_archivo, 'w') as nuevo_archivo:
                    pass
            except IOError:
                print(f"Error: No se pudo crear el archivo {nombre_archivo}")

    def cifrar_texto(self, texto):
        texto_cifrado = ''
        for c in texto:
            if c.isdigit():
                texto_cifrado += chr(((ord(c) - ord('0') + 2) % 10) + ord('0'))
            elif c.isalpha():
                if c.isupper():
                    texto_cifrado += chr(((ord(c) - ord('A') + 2) % 26) + ord('A'))
                else:
                    texto_cifrado += chr(((ord(c) - ord('a') + 2) % 26) + ord('a'))
        return texto_cifrado

    def descifrar_texto(self, texto):
        texto_descifrado = ''
        for c in texto:
            if c.isdigit():
                texto_descifrado += chr(((ord(c) - ord('0') - 2 + 10) % 10) + ord('0'))
            elif c.isalpha():
                if c.isupper():
                    texto_descifrado += chr(((ord(c) - ord('A') - 2 + 26) % 26) + ord('A'))
                else:
                    texto_descifrado += chr(((ord(c) - ord('a') - 2 + 26) % 26) + ord('a'))
        return texto_descifrado

    def esta_vacia(self):
        return self.Primero is None

    def salir_del_parqueadero(self, placa):
        actual = self.Primero
        encontrado = False

        while actual != self.Primero:
            coche = actual.dato

            if coche.placa == placa:
                if coche.hora_salida is not None:
                    actual = actual.siguiente
                    continue

                hora_actual = datetime.now()
                coche.set_hora_salida(hora_actual)
                actual.dato = coche

                print(f"El coche con placa {placa} ha salido del parqueadero.")
                encontrado = True
                break

            actual = actual.siguiente

        if encontrado:
            self.guardar_archivo("autos_historial.txt")
        else:
            print(f"Coche con placa {placa} no encontrado en el parqueadero.")        
    def guardar_propietarios(self, nombre_archivo):
        try:
            with open(nombre_archivo, 'w') as archivo:
                actual = self.Primero
                while True:
                    propietario = actual.dato
                    archivo.write(f"{propietario.get_nombre()},{propietario.get_apellido()},{propietario.get_cedula()},{propietario.get_correo()},")

                    placas = propietario.get_placas()
                    for i, placa in enumerate(placas):
                        archivo.write(placa)
                        if i < len(placas) - 1:
                            archivo.write(",")
                    archivo.write("\n")

                    actual = actual.siguiente
                    if actual == self.Primero:
                        break
        except IOError:
            print(f"Error: No se pudo abrir el archivo para escritura: {nombre_archivo}")

    def CargarPropietarios(self, nombre_archivo):
        try:
            with open(nombre_archivo, 'r') as archivo:
                for linea in archivo:
                    datos = linea.strip().split(',')
                    nombre, apellido, cedula, correo = datos[:4]
                    placas = datos[4:]

                    propietario = T(nombre, apellido, cedula, correo)
                    for placa in placas:
                        propietario.agregar_placa(placa)

                    self.insertar(propietario)
        except IOError:
            print(f"Error: No se pudo abrir el archivo para lectura: {nombre_archivo}")

    def busqueda_avanzada_propietario(self, criterio, valor_inicio, valor_fin=None):
        if self.Primero is None:
            print("La lista está vacía.")
            return

        if criterio != "hora":
            valor_inicio = valor_inicio.lower()

        actual = self.Primero
        encontrado = False

        while True:
            propietario = actual.dato
            if criterio == "cedula":
                cedula = propietario.get_cedula().lower()
                if cedula == valor_inicio:
                    print(f"========================================\n"
                          f"   PROPIETARIO REGISTRADO POR CÉDULA\n"
                          f"========================================\n"
                          f"{propietario}")
                    encontrado = True
            elif criterio == "correo":
                correo = propietario.get_correo().lower()
                if correo == valor_inicio:
                    print(f"========================================\n"
                          f"   PROPIETARIO REGISTRADO POR CORREO\n"
                          f"========================================\n"
                          f"{propietario}")
                    encontrado = True
            elif criterio == "nombre":
                nombre = propietario.get_nombre().lower()
                if nombre == valor_inicio:
                    print(f"========================================\n"
                          f"   PROPIETARIO REGISTRADO POR NOMBRE\n"
                          f"========================================\n"
                          f"{propietario}")
                    encontrado = True
            elif criterio == "apellido":
                apellido = propietario.get_apellido().lower()
                if apellido == valor_inicio:
                    print(f"========================================\n"
                          f"   PROPIETARIO REGISTRADO POR APELLIDO\n"
                          f"========================================\n"
                          f"{propietario}")
                    encontrado = True

            actual = actual.siguiente
            if actual == self.Primero:
                break

        if not encontrado:
            print(f"No se encontró ningún propietario con el criterio de búsqueda: {criterio}")





            
 
