import re

class Validaciones:
    def ingresar_string(self, msj: str) -> str:
        input_str = ""
        print(msj, end="", flush=True)

        while True:
            c = input()  # Aquí puedes personalizar para leer una sola tecla si lo deseas.
            if c.isalpha():
                c = c.upper()
                input_str += c
                print(c, end="", flush=True)
            elif c == '\b' and input_str:  # Si hay algo, elimina el último carácter.
                input_str = input_str[:-1]
                print("\b \b", end="", flush=True)
            elif c == '\r' and input_str:  # Enter
                break
            else:
                print("\a", end="", flush=True)  # Beep si no es un carácter válido.

        print()  # Nueva línea después del input
        return input_str

    def ingresar_cedula(self, msj: str) -> str:
        cedula = ""
        print(msj, end="", flush=True)

        while True:
            c = input()  # Lee el carácter.
            if c.isdigit():
                cedula += c
                print(c, end="", flush=True)
            elif c == '\b' and cedula:  # Si hay algo, elimina el último carácter.
                cedula = cedula[:-1]
                print("\b \b", end="", flush=True)
            elif c == '\r' and cedula:  # Enter
                break
            else:
                print("\a", end="", flush=True)  # Beep si no es un carácter válido.

        print()
        return cedula

    def ingresar_correo(self, msj: str) -> str:
        correo = input(msj)  # Solicitar el correo con input estándar
        return correo

    def validar_cedula(self, cedula: str) -> bool:
        if len(cedula) != 10:
            return False

        suma = 0
        for i in range(9):
            digito = int(cedula[i])
            if i % 2 == 0:
                digito *= 2
                if digito > 9:
                    digito -= 9
            suma += digito

        ultimo_digito = int(cedula[9])
        digito_verificador = (10 - (suma % 10)) % 10
        return ultimo_digito == digito_verificador

    def validar_correo(self, correo: str) -> bool:
        pattern = r"(\w+)(\.{1}\w+)*@(\w+)(\.{1}\w+)+"
        return bool(re.match(pattern, correo))
