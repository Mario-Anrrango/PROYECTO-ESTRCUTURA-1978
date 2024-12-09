#include "Lista.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <string> 
#include "Coche.h"
#include <algorithm> 
#include <cctype> 
#include <algorithm> 
#include <regex> 
#include <fstream>
#include <sstream>
#include <iomanip>


using namespace std;

template <typename T>
 ListaCircularDoble<T>::ListaCircularDoble()
{

primero = nullptr;
ultimo = nullptr;

}

template <typename T>
void ListaCircularDoble<T>::insertar(T dato){

Nodo<T>* nuevoCarro = new Nodo<T>(dato);

if(primero == nullptr){

primero = nuevoCarro; 
primero->setSiguiente(primero);
primero->setAnterior(primero);
ultimo = primero;

}else{

ultimo->setSiguiente(nuevoCarro);
nuevoCarro->setAnterior(ultimo);
ultimo = nuevoCarro;
ultimo->setSiguiente(primero);
primero->setAnterior(ultimo);
}

std::string nombreArchivo = "autos.txt";
GuardarArchivo("autos.txt");
}

template <typename T>
void ListaCircularDoble<T>::buscarPorPlaca(string placa) {
   
    if (primero == nullptr) {
        cout << "La lista está vacia." << endl;
        return;
    }

    Nodo<T>* aux = primero;
    do {
     
        if (aux->getDato().getPlaca() == placa) {
            cout << "========================================" << endl;
            cout << "   AUTOMOVIL REGISTRADO" << endl;
            cout << "========================================" << endl;
            cout << aux->getDato() << endl;
            return; 
        }
        aux = aux->getSiguiente();
    } while (aux != primero); 

 
    cout << "El coche con la placa " << placa << " no esta en el parqueadero." << endl;
}



template <typename T>
void ListaCircularDoble<T>::mostrar(Nodo<T>* primero) {
    if (primero == nullptr) {
        std::cout << "La lista esta vacia." << std::endl;
        return;
    }
    
    Nodo<T>* aux = primero;
    
  cout<< "AUTOMOVIL REGISTRADO"<<endl;
   cout << "========================================" << endl;
    cout << aux->getDato() << endl;
    
    aux = aux->getSiguiente();
    while (aux != primero) {  
        cout << aux->getDato() << endl;
        aux = aux->getSiguiente();
    }
    }

template <typename T>
void ListaCircularDoble<T>::eliminarPorPlaca( string placa) {
 
    if (primero == nullptr) {
        cout << "La lista está vacia." << endl;
        return;
    }

    Nodo<T>* aux = primero;
    Nodo<T>* anterior = nullptr;

   
    if (primero == ultimo && primero->getDato().getPlaca() == placa) {
        delete primero;
        primero = nullptr;
        ultimo = nullptr;
        cout << "El coche con la placa " << placa << " ha sido eliminado." << endl;
        return;
    }

   
    do {
        if (aux->getDato().getPlaca() == placa) {
          
            if (aux == primero) {
                primero = primero->getSiguiente();
                primero->setAnterior(ultimo);
                ultimo->setSiguiente(primero);
            }
         
            else if (aux == ultimo) {
                ultimo = ultimo->getAnterior();
                ultimo->setSiguiente(primero);
                primero->setAnterior(ultimo);
            }
           
            else {
                anterior = aux->getAnterior();
                anterior->setSiguiente(aux->getSiguiente());
                aux->getSiguiente()->setAnterior(anterior);
            }

            delete aux;
            cout << "El coche con la placa " << placa << " ha sido eliminado." << endl;
            return;
        }

        aux = aux->getSiguiente();
    } while (aux != primero);

   
    cout << "El coche con la placa " << placa << " no se encontro en el parqueadero." << endl;
}


template <typename T>
void ListaCircularDoble<T>::BusquedaAvanzada(string criterio, string valor) {
    if (primero == nullptr) {
        cout << "La lista esta vacia." << endl;
        return;
    }

   
    std::transform(valor.begin(), valor.end(), valor.begin(), ::tolower);

    Nodo<T>* aux = primero;
    bool encontrado = false;

    do {
       
            if (criterio == "marca") {
            string marca = aux->getDato().getMarca();
            std::transform(marca.begin(), marca.end(), marca.begin(), ::tolower);  
            if (marca == valor) {
                cout << "========================================" << endl;
                cout << "   AUTOMOVIL REGISTRADO POR MARCA" << endl;
                cout << "========================================" << endl;
                cout << aux->getDato() << endl;
                encontrado = true; 
            }
        }


        if (criterio == "modelo") {
            string modelo = aux->getDato().getModelo();
            std::transform(modelo.begin(), modelo.end(), modelo.begin(), ::tolower);  
            if (modelo == valor) {
                cout << "========================================" << endl;
                cout << "   AUTOMOVIL REGISTRADO POR MODELO" << endl;
                cout << "========================================" << endl;
                cout << aux->getDato() << endl;
                encontrado = true; 
            }
        }

      
        else if (criterio == "color") {
            string color = aux->getDato().getColor();
            std::transform(color.begin(), color.end(), color.begin(), ::tolower);  
            if (color == valor) {
                cout << "========================================" << endl;
                cout << "   AUTOMOVIL REGISTRADO POR COLOR" << endl;
                cout << "========================================" << endl;
                cout << aux->getDato() << endl;
                encontrado = true; 
            }
        }

        
        else if (criterio == "año" || criterio == "fecha") {
            std::chrono::system_clock::time_point horaIngreso = aux->getDato().getHora();
            std::time_t tiempo = std::chrono::system_clock::to_time_t(horaIngreso);
            std::tm* tm = std::localtime(&tiempo);

            char fecha[11];
            std::strftime(fecha, sizeof(fecha), "%d-%m-%Y", tm); 

            if (fecha == valor) {
                cout << "========================================" << endl;
                cout << "   AUTOMOVIL REGISTRADO POR FECHA" << endl;
                cout << "========================================" << endl;
                cout << aux->getDato() << endl;
                encontrado = true; 
            }
        }

        aux = aux->getSiguiente();  
    } while (aux != primero);  

    if (!encontrado) {
        cout << "No se encontro ningun automovil con el criterio de busqueda: " << criterio << " y valor: " << valor << endl;
    }
}
template <typename T>

void ListaCircularDoble<T>::CargarArchivo(string nombreArchivo){

std::ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
       
        std::istringstream ss(linea);
        std::string placa, modelo, color, marca, fechaIngreso;
        int año;

        
        if (std::getline(ss, placa, ',') &&
            std::getline(ss, modelo, ',') &&
            std::getline(ss, color, ',') &&
            std::getline(ss, marca, ',') &&
            std::getline(ss, fechaIngreso, ',') &&
            ss >> año) {  

           placa = descifrarTexto(placa);

            std::tm tm = {};
            std::istringstream ssFecha(fechaIngreso);
            ssFecha >> std::get_time(&tm, "%a %b %d %H:%M:%S %Y"); 
            auto horaIngreso = std::chrono::system_clock::from_time_t(std::mktime(&tm));

           
             T coche(placa, modelo, color, marca, año, horaIngreso);

            
               this->insertar(coche);

        } else {
            std::cerr << "Error: Formato de linea inválido: " << linea << std::endl;
        }
    }

    archivo.close();
}

template <typename T>
void ListaCircularDoble<T>::GuardarArchivo(string nombreArchivo) {
    std::ofstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << nombreArchivo << std::endl;
        return;
    }

    Nodo<T>* actual = primero;
    do {
       
        T coche = actual->getDato();
        
       std::string placaCifrada = cifrarTexto(coche.getPlaca());

        auto horaIngreso = coche.getHora(); 
        std::time_t horaIngresoTime = std::chrono::system_clock::to_time_t(horaIngreso);
        std::tm tmHoraIngreso = *std::localtime(&horaIngresoTime);

        
        archivo <<  placaCifrada << ","
                << coche.getModelo() << ","
                << coche.getColor() << ","
                << coche.getMarca() << ","
                << std::put_time(&tmHoraIngreso, "%a %b %d %H:%M:%S %Y") << ","
                << coche.getAño() << std::endl;

        actual = actual->getSiguiente();
    } while (actual != primero); 

    archivo.close();
}

template <typename T>
string ListaCircularDoble<T>::cifrarTexto(const std::string &texto)

{
    std::string textoCifrado = texto;
    
    for (char& c : textoCifrado) {
        if (isdigit(c)) {  
            c = ((c - '0' + 2) % 10) + '0';  
        } else if (isalpha(c)) {  
            if (isupper(c)) {
                c = ((c - 'A' + 2) % 26) + 'A';  
            } else {
                c = ((c - 'a' + 2) % 26) + 'a';  
            }
        }
    }
    
    return textoCifrado;
}

template <typename T>
string ListaCircularDoble<T>::descifrarTexto(const std::string &texto)
{
   std::string textoDescifrado = texto;
    
    for (char& c : textoDescifrado) {
        if (isdigit(c)) {  
            c = ((c - '0' - 2 + 10) % 10) + '0';  
        } else if (isalpha(c)) {  
            if (isupper(c)) {
                c = ((c - 'A' - 2 + 26) % 26) + 'A'; 
            } else {
                c = ((c - 'a' - 2 + 26) % 26) + 'a';  
            }
        }
    }
    
    return textoDescifrado;
}
