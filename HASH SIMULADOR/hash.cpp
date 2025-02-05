#include <iostream>
#include <vector>
#include <bitset>
#include <string>
#include <algorithm>

using namespace std;

string sumaBinaria(string a, string b) {
    string resultado = "";
    int carry = 0;
    int i = a.length() - 1, j = b.length() - 1;

    while (i >= 0 || j >= 0 || carry) {
        int bitA = (i >= 0) ? a[i] - '0' : 0;
        int bitB = (j >= 0) ? b[j] - '0' : 0;
        
        int suma = bitA + bitB + carry;
        resultado += (suma % 2) + '0';
        carry = suma / 2;
        
        i--; j--;
    }

    reverse(resultado.begin(), resultado.end());
    return resultado;
}

const int TAMANIO_TABLA = 13;

int funcionHash(const string& clave) {
    unsigned int hash = 0;

    string claveInvertida = clave;
    reverse(claveInvertida.begin(), claveInvertida.end());

    cout << "Procesando clave: " << claveInvertida << endl;
    int index = 0;
    int totalLetras = claveInvertida.length();

    for (char c : claveInvertida) {
        unsigned int valor = static_cast<unsigned int>(c);
        cout << "Letra: '" << c << "' Decimal: " << valor << " Binario: " << bitset<32>(valor) << endl;

        string binHash = bitset<32>(hash).to_string();
        string binValor = bitset<32>(valor).to_string();

        cout << "Hash antes de la suma: " << binHash << " (" << hash << ")" << endl;
        cout << "Valor ASCII en binario: " << binValor << " (" << valor << ")" << endl;

        string binSuma = sumaBinaria(binHash, binValor);

        cout << "Resultado de la suma binaria: " << binSuma << endl;

        if (index < totalLetras - 1) { // Solo hacer XOR y agregar ceros si NO es la última letra
            string primeros4 = binSuma.substr(0, 4);
            cout << "Primeros 4 bits extraidos: " << primeros4 << endl;

            for (int i = 11; i <= 14; i++) {
                binSuma[i] = (binSuma[i] == primeros4[i - 11]) ? '0' : '1';
            }

            binSuma = binSuma.substr(4) + "0000";

            cout << "Binario despues de XOR y agregar ceros: " << binSuma << endl;
        }

        hash = bitset<32>(binSuma).to_ulong();

        cout << "XOR acumulado: " << bitset<32>(hash) << " (" << hash << ")" << endl;

        index++;
    }
    
    hash = hash % TAMANIO_TABLA;
    cout << "Hash final (mod " << TAMANIO_TABLA << "): " << hash << endl;
    cout << "---------------------------------" << endl;

    return hash;
}

class TablaHash {
private:
    vector<string> tabla;
public:
    TablaHash() : tabla(TAMANIO_TABLA, "") {}

    void insertar(const string& clave) {
        int valorHash = funcionHash(clave);
        int indice = valorHash;
        while (!tabla[indice].empty()) {
            indice = (indice + 1) % TAMANIO_TABLA;
        }
        tabla[indice] = clave;
        cout << "Insertado \"" << clave << "\" en el Indice " << indice << " con valor hash " << valorHash << endl;
    }

    bool buscar(const string& clave) {
        int indice = funcionHash(clave);
        int inicio = indice;
        while (!tabla[indice].empty()) {
            if (tabla[indice] == clave) return true;
            indice = (indice + 1) % TAMANIO_TABLA;
            if (indice == inicio) break;
        }
        return false;
    }

    void mostrar() {
        for (int i = 0; i < TAMANIO_TABLA; i++) {
            if (!tabla[i].empty()) {
                cout << i << ": " << tabla[i] << endl;
            }
        }
    }
};

int main() {
    TablaHash tablaHash;
    string entrada;
    
    cout << "Ingresa cadenas para insertar en la tabla hash (escribe 'fin' para terminar):\n";
    while (true) {
        cin >> entrada;
        if (entrada == "fin") break;
        tablaHash.insertar(entrada);
    }
    
    cout << "\nContenido de la tabla hash:\n";
    tablaHash.mostrar();
    
    return 0;
}
