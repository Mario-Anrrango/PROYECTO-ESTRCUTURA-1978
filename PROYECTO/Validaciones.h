#pragma once

#include <iostream>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <cctype>

using namespace std;

class Validaciones
{
public:
    inline string ingresarString(const string &msj);
    inline string ingresarCedula(const string &msj);
};

inline string Validaciones::ingresarString(const string &msj)
{
    string input;
    char c;

    cout << msj;

    while (true)
    {
        c = getch();

        if (isalpha(c))
        {
            input += c;
            cout << c;
        }
        else if (c == '\b' && !input.empty())
        {
            input.pop_back();
            cout << "\b \b";
        }
        else if (c == '\r')
        {
            if (!input.empty())
            {
                break;
            }
            else
            {
                cout << "\a";
            }
        }
        else
        {
            cout << "\a";
        }
    }

    cout << endl;
    return input;
}

inline string Validaciones::ingresarCedula(const string &msj)
{
    string input;
    char c;

    cout << msj;

    while (true)
    {
        c = getch();

        if (isdigit(c))  
        {
            input += c;
            cout << c;
        }
        else if (c == '\b' && !input.empty())  
        {
            input.pop_back();
            cout << "\b \b";
        }
        else if (c == '\r')  
        {
            if (input.length() == 10)  
            {
                break;
            }
            else
            {
                cout << "\a";  
                cout << "\nLa cédula debe tener 10 dígitos. Intente nuevamente: ";
                input.clear();
                cout << msj;
            }
        }
        else
        {
            cout << "\a";  
        }
    }

    cout << endl;
    return input;
}

