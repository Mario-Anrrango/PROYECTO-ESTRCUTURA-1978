import os
import subprocess
import msvcrt

def get_key():
    while True:
        if msvcrt.kbhit():
            key = msvcrt.getch()
            if key == b'\xe0':  # Special keys (arrows, f keys, ins, del, etc.)
                key = msvcrt.getch()
                return key
            else:
                return key

def print_menu(selected_index):
    menu_items = ["Lista Simple", "Lista Doble", "Lista Circular Doble", "Lista Circular Simple", "Salir"]
    print("========================================")
    print("      Menu de Proyectos de Listas")
    print("========================================")
    for i, item in enumerate(menu_items):
        if i == selected_index:
            print(f" > {item} <")
        else:
            print(f"   {item}")
    print("========================================")

def main():
    rutas = {
        0: {
            "ruta_autos": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE\\autos.txt",
            "ruta_autos_historial": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE\\autos_historial.txt",
            "ruta_propietarios": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE\\propietarios.txt",
            "ruta_exe": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE\\ListaSimple.exe",
            "ruta_dir": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE"
        },
        1: {
            "ruta_autos": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA DOBLE\\autos.txt",
            "ruta_autos_historial": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA DOBLE\\autos_historial.txt",
            "ruta_propietarios": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA DOBLE\\propietarios.txt",
            "ruta_exe": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA DOBLE\\ListaDoble.exe",
            "ruta_dir": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA DOBLE"
        },
        2: {
            "ruta_autos": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR DOBLE\\autos.txt",
            "ruta_autos_historial": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR DOBLE\\autos_historial.txt",
            "ruta_propietarios": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR DOBLE\\propietarios.txt",
            "ruta_exe": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR DOBLE\\ListaCircularDoble.exe",
            "ruta_dir": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR DOBLE"
        },
        3: {
            "ruta_autos": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR SIMPLE\\autos.txt",
            "ruta_autos_historial": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR SIMPLE\\autos_historial.txt",
            "ruta_propietarios": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR SIMPLE\\propietarios.txt",
            "ruta_exe": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR SIMPLE\\ListaCircularSimple.exe",
            "ruta_dir": "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR SIMPLE"
        }
    }

    selected_index = 0
    while True:
        os.system('cls')  # Use 'cls' for Windows
        print_menu(selected_index)
        key = get_key()
        if key == b'H':  # Up arrow
            selected_index = (selected_index - 1) % 5
        elif key == b'P':  # Down arrow
            selected_index = (selected_index + 1) % 5
        elif key == b'\r':  # Enter key
            if selected_index == 4:
                print("Saliendo del programa...")
                break
            else:
                ruta = rutas.get(selected_index)
                if ruta:
                    os.chdir(ruta["ruta_dir"])
                    subprocess.run(ruta["ruta_exe"], shell=True)
                else:
                    print("Opción no válida.")
                break

if __name__ == "__main__":
    main()