#include <iostream>
#include "Coche.h"
#include "Propietario.h"

int main()
{
   
    std::string nombreArchivoPropietarios = "propietarios.txt";
    ListaCircularDoble<Propietario> listaPropietarios;
    listaPropietarios.CargarArchivoPropietario(NombreArchivoPropietarios);;

    ListaCircularDoble<Coche> listaCochesHistorial;
    std::string nombreArchivoHistorial = "autos_historial.txt";
    listaCochesHistorial.CargarArchivo("autos_historial.txt");
     
    ListaCircularDoble<Coche> listaCoches;
    std::string nombreArchivo = "autos.txt";
    listaCoches.CargarArchivo("autos.txt");


    Coche coche;

    coche.menu(listaCoches,listaCochesHistorial);

    return 0;
}