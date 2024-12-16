#include "Cedula.h"


string Cedula::ingresarCedula(Nodo<Propietario>* aux)  
{
    string cedula;

    while (true)
    {
        cout << "Ingrese el número de cédula: ";
        getline(cin, cedula);

        cedula.erase(remove(cedula.begin(), cedula.end(), ' '), cedula.end());

        if (cedula.length() != 10)
        {
            cout << "\nLa cédula debe tener exactamente 10 dígitos. Intente de nuevo." << endl;
            continue;
        }

        if (!regex_match(cedula, regex("^[0-9]{10}$")))
        {
            cout << "\nLa cédula debe contener solo números. Intente de nuevo." << endl;
            continue;
        }

        if (!validarCodigoProvincia(cedula))
        {
            cout << "\nEl código de provincia no es válido. Intente de nuevo." << endl;
            continue;
        }

        if (!validarDigitoVerificador(cedula))
        {
            cout << "\nEl número de cédula no es válido. Intente de nuevo." << endl;
            continue;
        }

        break;
    }

    return cedula;
}

bool Cedula::validarCodigoProvincia(const string &cedula)
{
    int codigoProvincia = stoi(cedula.substr(0, 2));

    return codigoProvincia >= 1 && codigoProvincia <= 24;
}

bool Cedula::validarDigitoVerificador(const string &cedula)
{
    int suma = 0;
    int coeficientes[] = {2, 1};

    for (int i = 0; i < 9; ++i)
    {
        int digito = cedula[i] - '0';
        int producto = digito * coeficientes[i % 2];

        if (producto > 9)
        {
            producto -= 9;
        }

        suma += producto;
    }

    int digitoVerificador = cedula[9] - '0';
    int digitoEsperado = (10 - (suma % 10)) % 10;

    return digitoVerificador == digitoEsperado;
}
