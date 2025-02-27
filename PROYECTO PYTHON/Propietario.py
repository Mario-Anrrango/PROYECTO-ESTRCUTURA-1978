from Validaciones import Validaciones


class Propietario:
    def __init__(self, nombre="", apellido="", cedula="", correo="", placas=None):
        """
        Constructor de la clase Propietario.
        Inicializa los atributos del propietario.
        """
        if placas is None:
            placas = []
        self.nombre = nombre
        self.apellido = apellido
        self.cedula = cedula
        self.correo = correo
        self.placas = placas

    def set_nombre(self, nombre):
        """
        Establece el nombre del propietario.
        """
        self.nombre = nombre

    def set_apellido(self, apellido):
        """
        Establece el apellido del propietario.
        """
        self.apellido = apellido

    def set_cedula(self, cedula):
        """
        Establece la cédula del propietario.
        """
        self.cedula = cedula

    def set_correo(self, correo):
        """
        Establece el correo electrónico del propietario.
        """
        self.correo = correo

    def eliminar_placa(self, placa):
        """
        Elimina una placa de la lista de placas del propietario.
        """
        if placa in self.placas:
            self.placas.remove(placa)
            print(f"Placa {placa} eliminada correctamente.")
        else:
            print("La placa no se encontró en las placas del propietario.")
        return self.placas

    def get_nombre(self):
        """
        Obtiene el nombre del propietario.
        """
        return self.nombre

    def get_apellido(self):
        """
        Obtiene el apellido del propietario.
        """
        return self.apellido

    def get_cedula(self):
        """
        Obtiene la cédula del propietario.
        """
        return self.cedula

    def get_correo(self):
        """
        Obtiene el correo electrónico del propietario.
        """
        return self.correo

    def set_placas(self, placas):
        """
        Establece la lista de placas del propietario.
        """
        self.placas = placas

    def agregar_placa(self, placa):
        """
        Agrega una placa a la lista de placas del propietario.
        """
        self.placas.append(placa)

    def get_placas(self):
        """
        Obtiene la lista de placas del propietario.
        """
        return self.placas

    def __str__(self):
        """
        Representación en cadena de texto del propietario.
        """
        propietario_info = (
            f"Nombre: {self.get_nombre()}\n"
            f"Apellido: {self.get_apellido()}\n"
            f"Cedula: {self.get_cedula()}\n"
            f"Correo: {self.get_correo()}\n"
            f"{'-'*40}\n"
        )
        placas_info = "Placas: "
        if not self.get_placas():
            placas_info += "N/A"
        else:
            placas_info += " ".join(self.get_placas())
        placas_info += f"\n{'-'*40}"
        return propietario_info + placas_info

    @staticmethod
    def agregar_propietario():
        """
        Método estático para crear un nuevo propietario.
        Solicita los datos del propietario y los valida.
        """
        validaciones = Validaciones()
        nombre = validaciones.ingresar_string("Ingrese el nombre del propietario: ")
        apellido = validaciones.ingresar_string("Ingrese el apellido del propietario: ")

        cedula = ""
        while not validaciones.validar_cedula(cedula):
            cedula = validaciones.ingresar_cedula("Ingrese la cedula del propietario: ")
            if not validaciones.validar_cedula(cedula):
                print("Cédula inválida. Intente de nuevo.")

        correo = ""
        while not validaciones.validar_correo(correo):
            correo = validaciones.ingresar_correo("Ingrese el correo electrónico del propietario: ")
            if not validaciones.validar_correo(correo):
                print("Correo inválido. Intente de nuevo.")

        nuevo_propietario = Propietario(nombre, apellido, cedula, correo)
        print("Propietario creado exitosamente.")
        return nuevo_propietario