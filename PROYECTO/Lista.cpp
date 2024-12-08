#include "Lista.h"
#include <iostream> 
#include "Coche.h"

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


    
   

