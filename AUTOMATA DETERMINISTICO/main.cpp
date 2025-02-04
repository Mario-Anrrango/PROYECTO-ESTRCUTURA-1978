#include "NFA.h"
#include "DFA.h"
#include "Converter.h"
#include <iostream>
#include <set>

using namespace std;

int main() {
    int numStates, initialState, numFinalStates, numTransitions;
    set<int> finalStates;
    set<char> alphabet;

    // Solicitar número de estados
    cout << "Ingrese el número de estados del NFA: ";
    cin >> numStates;

    // Ingresar estado inicial
    cout << "Ingrese el estado inicial: ";
    cin >> initialState;

    // Ingresar estados finales
    cout << "Ingrese la cantidad de estados finales: ";
    cin >> numFinalStates;

    cout << "Ingrese los estados finales (separados por espacio): ";
    for (int i = 0; i < numFinalStates; i++) {
        int state;
        cin >> state;
        finalStates.insert(state);
    }

    // Crear NFA
    NFA nfa(initialState, finalStates);

    // Ingresar transiciones
    cout << "Ingrese la cantidad de transiciones: ";
    cin >> numTransitions;

    cout << "Ingrese las transiciones en formato: estado_origen simbolo estado_destino\n";
    for (int i = 0; i < numTransitions; i++) {
        int from, to;
        char symbol;
        cin >> from >> symbol >> to;
        nfa.addTransition(from, symbol, to);
        alphabet.insert(symbol); // Agregar símbolo al alfabeto
    }

    // Mostrar NFA
    cout << "\n==== NFA ====\n";
    nfa.printNFA();

    // Convertir NFA a DFA
    DFA dfa = Converter::convert(nfa, alphabet);

    // Mostrar el DFA resultante
    cout << "\n==== DFA ====\n";
    dfa.printDFA();

    return 0;
}

