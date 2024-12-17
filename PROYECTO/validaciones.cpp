#include "Validaciones.h"  
#include <iostream>
#include <conio.h>

string Validaciones::ingresarString(const string &msj)
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
