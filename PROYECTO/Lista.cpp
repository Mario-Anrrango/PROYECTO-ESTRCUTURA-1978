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

    
   

