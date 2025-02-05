#include <iostream>
#include <set>
#include <vector>
#include "NFA.h"
#include "DFA.h"
#include "Converter.h"
#include "GraphRenderer.h"

using namespace std;

int main() {
    int numStates;           // Número total de estados
    int initialState;        // Estado inicial del NFA
    set<int> finalStates;    // Estados finales del NFA
    int numFinalStates;      // Cantidad de estados finales a ingresar
    int numTransitions;      // Cantidad de transiciones a ingresar
    set<char> alphabet;      // Alfabeto (se extrae de los símbolos ingresados)

    // Solicitar el número total de estados
    cout << "Ingrese el numero total de estados: ";
    cin >> numStates;

    // Solicitar el estado inicial
    cout << "Ingrese el estado inicial: ";
    cin >> initialState;

    // Solicitar los estados finales
    cout << "Ingrese la cantidad de estados finales: ";
    cin >> numFinalStates;
    cout << "Ingrese los estados finales: ";
    for (int i = 0; i < numFinalStates; i++) {
        int state;
        cin >> state;
        finalStates.insert(state);
    }

    // Crear el NFA
    NFA nfa(initialState, finalStates);

    // Solicitar las transiciones
    cout << "Ingrese la cantidad de transiciones: ";
    cin >> numTransitions;
    cout << "Ingrese las transiciones en formato: estado_origen simbolo estado_destino\n";
    for (int i = 0; i < numTransitions; i++) {
        int from, to;
        char symbol;
        cin >> from >> symbol >> to;
        nfa.addTransition(from, symbol, to);
        alphabet.insert(symbol);
    }

    // Mostrar el NFA
    cout << "\n==== NFA ====\n";
    nfa.printNFA();

    // Convertir NFA a DFA
    DFA dfa = Converter::convert(nfa, alphabet);

    // Mostrar el DFA resultante
    cout << "\n==== DFA ====\n";
    dfa.printDFA();

    // Extraer las transiciones del DFA para el renderizador gráfico.
    // Aquí suponemos que dfa.getTransitions() devuelve un std::map<std::set<int>, std::map<char, std::set<int>>>
    // Se toma el primer elemento del conjunto para visualización.
    vector<Transition> transitions;
    set<int> dfaFinalStates;
    for (const auto& fromPair : dfa.getTransitions()) {
        int fromState = *fromPair.first.begin();
        for (const auto& symbolPair : fromPair.second) {
            char symbol = symbolPair.first;
            int toState = *symbolPair.second.begin();
            transitions.push_back(Transition{fromState, toState, symbol});
        }
    }

    for (const auto& state : dfa.getFinalStates()) {
        dfaFinalStates.insert(state);
    }

    // Inicializar y ejecutar el renderizador gráfico pasando el número total de estados
    GraphRenderer renderer(800, 600, numStates);
    renderer.drawGraph(transitions, dfaFinalStates);
    renderer.run();

    return 0;
}
