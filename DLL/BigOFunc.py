import subprocess

def run_cpp_analyzer(filename):
    """
    Ejecuta el ejecutable de C++ que analiza el archivo fuente y devuelve su salida.
    """
    print(f"Ejecutando main.exe con el archivo: {filename}")
    try:
        result = subprocess.run(
            ["main.exe", filename.strip()],
            capture_output=True,
            text=True,
            check=True
        )
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        print("Error ejecutando el analizador C++:", e)
        return ""

def open_matlab_with_data(data):
    """
    Abre MATLAB pasando la cadena 'data' al script 'simulateComplexity.m'.
    
    Se:
      - Duplican las comillas simples para evitar problemas en MATLAB.
      - Se reemplazan los saltos de línea por la secuencia literal '\\n'.
    """
    # Duplicar las comillas simples
    safe_data = data.replace("'", "''")
    # Reemplazar saltos de línea reales por la secuencia literal "\n"
    safe_data = safe_data.replace("\n", "\\n")
    matlab_command = f"simulateComplexity('{safe_data}');"
    try:
        subprocess.Popen(["matlab", "-nosplash", "-nodesktop", "-r", matlab_command])
    except Exception as e:
        print("Error al abrir MATLAB:", e)

def main():
    filename = input("Ingrese la ruta del archivo .cpp: ").strip()
    print(f"Ruta ingresada: {filename}")

    if not filename:
        print("Error: No se ingresó una ruta válida.")
        return

    cpp_output = run_cpp_analyzer(filename)
    
    if not cpp_output:
        print("No se obtuvo salida del analizador C++.")
        return

    # Corregir problemas de codificación (por ejemplo, "FunciÃ³n" -> "Función")
    cpp_output = cpp_output.replace("Ã³", "ó")
    
    print("Salida del analizador C++:")
    print(cpp_output)
    
    print("Abriendo MATLAB con los datos...")
    open_matlab_with_data(cpp_output)

if __name__ == "__main__":
    print("Iniciando el programa...")
    main()
    print("Programa finalizado.")
