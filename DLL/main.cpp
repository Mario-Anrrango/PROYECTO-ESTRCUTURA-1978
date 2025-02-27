#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <windows.h>

typedef void (*AnalyzeFunctionsPtr)(const char*);

int main(int argc, char* argv[]) {
    HINSTANCE hDLL = LoadLibrary("BigOFunc.dll");
    if (!hDLL) {
        std::cerr << "No se pudo cargar la DLL" << std::endl;
        return 1;
    }

    AnalyzeFunctionsPtr AnalyzeFunctions = (AnalyzeFunctionsPtr)GetProcAddress(hDLL, "AnalyzeFunctions");
    if (!AnalyzeFunctions) {
        std::cerr << "No se encontró la función en la DLL" << std::endl;
        FreeLibrary(hDLL);
        return 1;
    }

    std::string filepath;
    if (argc > 1) {
        filepath = argv[1];
    } else {
        do {
            std::cout << "Ingrese la ruta del archivo .cpp: ";
            std::getline(std::cin, filepath);
            std::ifstream file(filepath);
            if (!file) {
                std::cerr << "Error: No se encontró el archivo en la ruta especificada. Intente de nuevo.\n";
            } else {
                file.close();
                break;
            }
        } while (true);
    }
    
    AnalyzeFunctions(filepath.c_str());

    FreeLibrary(hDLL);
    return 0;
}
