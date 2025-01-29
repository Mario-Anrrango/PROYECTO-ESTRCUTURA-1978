#include "Estacionamiento.h"

Estacionamiento::Estacionamiento() {
    std::srand(0);
}

void Estacionamiento::ocuparEspacio(int espacio, Coche& coche) {
    if (espacio >= 0 && espacio < TAMANIO && !espacioOcupado(espacio)) {
        espaciosOcupados[espacio] = coche;  
        std::cout << "El coche con placa " << coche.getPlaca() << " ha entrado en el parqueadero " 
                  << "en el espacio " << espacio + 1 << "." << std::endl;  // sumamos 1 para hacerlo más amigable

    } else {
        std::cout << "Espacio no válido o ya ocupado." << std::endl;
    }
}

void Estacionamiento::liberarEspacio(const std::string& placa) {
    try {
        
        int espacio = obtenerEspacioPorPlaca(placa); 
        
       
        if (espacioOcupado(espacio)) {
            espaciosOcupados.erase(espacio);  
            std::cout << "Espacio " << espacio << " liberado." << std::endl;
        } else {
            std::cout << "Espacio no ocupado." << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl; 
    }
}

int Estacionamiento::obtenerEspacioPorPlaca(const std::string& placa) {
   
   std::cout << "=== DEBUG: Contenido de espaciosOcupados ===" << std::endl;
if (espaciosOcupados.empty()) {
    std::cout << "El mapa está vacío, no hay coches almacenados." << std::endl;
} else {
    for (const auto& pair : espaciosOcupados) {
        std::cout << "Espacio: " << pair.first << " | Placa: " << pair.second.getPlaca() << std::endl;
    }
}
std::cout << "==========================================" << std::endl;
    for (const auto& pair : espaciosOcupados) {
        const Coche& coche = pair.second;
        std::cout << "  Comparando con placa: " << coche.getPlaca() 
                  << " en espacio " << pair.first << std::endl;

        if (coche.getPlaca() == placa) {
            std::cout << "  -> Coche encontrado en el espacio " << pair.first << std::endl;
            return pair.first;
        }
    }

    std::cout << "  -> Coche NO encontrado." << std::endl;
    throw std::invalid_argument("Coche no encontrado en el estacionamiento.");
}



void Estacionamiento::mostrarEstacionamiento() {
    std::cout << "Estado del Parqueadero:\n";
    
   std::cout << "\n";

   std::cout << " _________" << std::endl;
   std::cout << "| E1 | S1 |" << std::endl;
   std::cout << "|    |    |_____________" << std::endl;
   std::cout << "|    |_______________   |" << std::endl;
   std::cout << "|__________________  |  |" << std::endl;
    for (int i = 0; i < TAMANIO; ++i) {
       
        if (espacioOcupado(i)) {
            std::cout << "[X] ";  
        } else {
            std::cout << "[ ] ";  
         }

   
    if ((i + 1) % 5 == 0) {
        std::cout << "    ";  
    }

    if ((i + 1) % 10 == 0) {
        std::cout << std::endl;  
    }
    }
   std::cout << "                  |  |  |_________" << std::endl;
   std::cout << "                  |  |_______     |" << std::endl;
   std::cout << "                  |_____     |    |" << std::endl;
   std::cout << "                        |    |    |" << std::endl;
   std::cout << "                        | E2 | S2 |" << std::endl;
   std::cout << "                        |____|____|" << std::endl;
   

    std::cout << std::endl;
}

int Estacionamiento::obtenerEspacioAleatorio() {
    int espacio = rand() % TAMANIO;  
    
    while (espacioOcupado(espacio)) {  
        espacio = rand() % TAMANIO;  
    }
    
    return espacio;  
}

int Estacionamiento::getNumeroEspacios() const {
    return TAMANIO; 
}

bool Estacionamiento::espacioOcupado(int espacio) {
    return espaciosOcupados.find(espacio) != espaciosOcupados.end();  
}

Coche Estacionamiento::obtenerCocheEnEspacio(int espacio) {
        if (espacioOcupado(espacio)) {
            return espaciosOcupados[espacio];
        }
        return Coche();
    }


void Estacionamiento::vaciarEstacionamiento() {
    espaciosOcupados.clear();  
    std::cout << "Estacionamiento vaciado correctamente." << std::endl;
}

    vector<int> Estacionamiento::obtenerTodosLosEspacios() {
        vector<int> espacios;
        for (const auto& it : espaciosOcupados) {
            espacios.push_back(it.first);
        }
        return espacios;
    }
        int Estacionamiento::buscarCocheCercano(string salida) {
        vector<int> espacios = obtenerTodosLosEspacios();

        if (espacios.empty()) {
            cout << "No hay coches en el estacionamiento." << endl;
            return -1;
        }

       
        vector<int> prioridad = {4, 5, 3, 6, 2, 7, 1, 8, 0, 9};

       
        auto prioridadOrdenamiento = [&](int a, int b) {
            string strA = to_string(a);
            string strB = to_string(b);

            
            if (salida == "1") { 
                if (strA[0] != strB[0])
                    return strA[0] < strB[0];
            } else if (salida == "2") {
                if (strA[0] != strB[0])
                    return strA[0] > strB[0];
            }

            
            if (strA.length() > 1 && strB.length() > 1) {
                int segundoA = strA[1] - '0';
                int segundoB = strB[1] - '0';

                return find(prioridad.begin(), prioridad.end(), segundoA) <
                       find(prioridad.begin(), prioridad.end(), segundoB);
            }

            return false;
        };

       
        sort(espacios.begin(), espacios.end(), prioridadOrdenamiento);

        return espacios.front(); 
    }

    