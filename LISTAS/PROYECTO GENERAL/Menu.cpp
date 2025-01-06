#include <iostream>
#include <conio.h>
#include <windows.h>  // For system("cls") and SetCurrentDirectory
#include <vector>
#include <string>

using namespace std;

int mostrarMenu(const vector<string>& opciones) {
    int seleccion = 0;
    int numOpciones = opciones.size();

    while (true) {
        system("cls");  // Clear the screen

        cout << "========================================" << endl;
        cout << "      Menu de Proyectos de Listas       " << endl;
        cout << "========================================" << endl;

        for (int i = 0; i < numOpciones; ++i) {
            if (i == seleccion) {
                cout << " > " << opciones[i] << " < " << endl;  
            } else {
                cout << "   " << opciones[i] << endl; 
            }
        }

        cout << "========================================" << endl;

      
        char tecla = _getch();

        
        if (tecla == 'w' || tecla == 72) {
            seleccion = (seleccion - 1 + numOpciones) % numOpciones;
        } else if (tecla == 's' || tecla == 80) {
            seleccion = (seleccion + 1) % numOpciones;
        } else if (tecla == 13) {  
            return seleccion;
        }
    }
}

int main() {
    string rutaAutos, rutaAutosHistorial, rutaPropietarios;
    string rutaExe;
    string rutaDir;

    vector<string> opciones = {"Lista Simple", "Lista Doble", "Lista Circular Doble", "Lista Circular Simple", "Salir"};
    int seleccion = mostrarMenu(opciones);

    switch (seleccion) {
        case 0: 
            rutaAutos = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE\\autos.txt";
            rutaAutosHistorial = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE\\autos_historial.txt";
            rutaPropietarios = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE\\propietarios.txt";
            rutaExe = "\"C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE\\ListaSimple.exe\"";
            rutaDir = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE";
            break;
        case 1: 
            rutaAutos = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA DOBLE\\autos.txt";
            rutaAutosHistorial = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA DOBLE\\autos_historial.txt";
            rutaPropietarios = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA DOBLE\\propietarios.txt";
            rutaExe = "\"C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA DOBLE\\ListaDoble.exe\"";
            rutaDir = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA DOBLE";
            break;
        case 2: 
            rutaAutos = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR DOBLE\\autos.txt";
            rutaAutosHistorial = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR DOBLE\\autos_historial.txt";
            rutaPropietarios = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR DOBLE\\propietarios.txt";
            rutaExe = "\"C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR DOBLE\\ListaCircularDoble.exe\"";
            rutaDir = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR DOBLE";
            break;
        case 3: 
            rutaAutos = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA CIRCULAR SIMPLE\\autos.txt";
            rutaAutosHistorial = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE CIRCULAR\\autos_historial.txt";
            rutaPropietarios = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE CIRCULAR\\propietarios.txt";
            rutaExe = "\"C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE CIRCULAR\\ListaCircularSimple.exe\"";
            rutaDir = "C:\\REPOSITORIO\\PROYECTO-ESTRCUTURA-1978\\LISTAS\\LISTA SIMPLE CIRCULAR";
            break;
        case 4:
            cout << "Saliendo del programa..." << endl;
            return 0;
        default:
            cout << "Opción no válida." << endl;
            return 1;
    }

    // Cambiar el directorio de trabajo
    if (!SetCurrentDirectory(rutaDir.c_str())) {
        cerr << "Error al cambiar el directorio de trabajo a " << rutaDir << endl;
        return 1;
    }

    // Ejecutar el archivo .exe correspondiente
    system(rutaExe.c_str());

    return 0;
}