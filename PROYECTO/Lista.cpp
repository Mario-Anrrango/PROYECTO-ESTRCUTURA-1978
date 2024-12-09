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