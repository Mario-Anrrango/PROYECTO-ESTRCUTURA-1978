#include <iostream>
#include "Coche.h"
#include "Lista.h"
#include "Propietario.h"

int main()
{
    ListaCircularDoble<Propietario> listaPropietarios;
    std::string nombreArchivoPropietarios = "propietarios.txt";


    ListaCircularDoble<Coche> listaCochesHistorial;
    std::string nombreArchivoHistorial = "autos_historial.txt";
    listaCochesHistorial.CargarArchivo("autos_historial.txt");
     
    ListaCircularDoble<Coche> listaCoches;
    std::string nombreArchivo = "autos.txt";
    listaCoches.CargarArchivo("autos.txt");


    Coche coche;

    coche.menu(listaCoches,listaCochesHistorial,listaPropietarios);

    return 0;
}