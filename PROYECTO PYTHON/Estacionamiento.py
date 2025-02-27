import random


class Coche:
    def __init__(self, placa):
        self.placa = placa
    
    def get_placa(self):
        return self.placa


class Estacionamiento:
    TAMANIO = 100  # Tamaño del estacionamiento

    def __init__(self):
        self.espacios_ocupados = {}

    def ocupar_espacio(self, espacio, coche):
        if 0 <= espacio < self.TAMANIO and not self.espacio_ocupado(espacio):
            self.espacios_ocupados[espacio] = coche
        else:
            print("Espacio no válido o ya ocupado.")

    def liberar_espacio(self, placa):
        try:
            espacio = self.obtener_espacio_por_placa(placa)
            if self.espacio_ocupado(espacio):
                del self.espacios_ocupados[espacio]
                print(f"Espacio {espacio} liberado.")
            else:
                print("Espacio no ocupado.")
        except ValueError as e:
            print(e)

    def obtener_espacio_por_placa(self, placa):
        print("=== DEBUG: Contenido de espaciosOcupados ===")
        if not self.espacios_ocupados:
            print("El mapa está vacío, no hay coches almacenados.")
        else:
            for espacio, coche in self.espacios_ocupados.items():
                print(f"Espacio: {espacio} | Placa: {coche.get_placa()}")
        print("==========================================")

        for espacio, coche in self.espacios_ocupados.items():
            print(f"  Comparando con placa: {coche.get_placa()} en espacio {espacio}")
            if coche.get_placa() == placa:
                print(f"  -> Coche encontrado en el espacio {espacio}")
                return espacio

        print("  -> Coche NO encontrado.")
        raise ValueError("Coche no encontrado en el estacionamiento.")

    def mostrar_estacionamiento(self):
        print("Estado del Parqueadero:")
        for i in range(self.TAMANIO):
            if self.espacio_ocupado(i):
                print("[X]", end=" ")  # Espacio ocupado
            else:
                print("[ ]", end=" ")  # Espacio libre

            if (i + 1) % 5 == 0:
                print("   ", end="")  # Espacios visuales

            if (i + 1) % 10 == 0:
                print()  # Nueva línea cada 10 espacios

        print()

    def obtener_espacio_aleatorio(self):
        espacio = random.randint(0, self.TAMANIO - 1)

        while self.espacio_ocupado(espacio):
            espacio = random.randint(0, self.TAMANIO - 1)

        return espacio

    def get_numero_espacios(self):
        return self.TAMANIO

    def espacio_ocupado(self, espacio):
        return espacio in self.espacios_ocupados

    def obtener_coche_en_espacio(self, espacio):
        if self.espacio_ocupado(espacio):
            return self.espacios_ocupados[espacio]
        else:
            raise ValueError("El espacio no está ocupado.")

    def vaciar_estacionamiento(self):
        self.espacios_ocupados.clear()
        print("Estacionamiento vaciado correctamente.")
