#include "DFA.h"

void DFA::addTransition(set<int> from, char symbol, set<int> to) {
    transitions[from][symbol] = to;
}

void DFA::addState(set<int> state) {
    states.insert(state);
}

void DFA::addFinalState(int state) {
    finalStates.insert(state);
}

void DFA::printDFA() const {
    cout << "DFA Transitions:\n";
    for (const auto& [stateSet, transitionMap] : transitions) {
        for (const auto& [symbol, nextStateSet] : transitionMap) {
            cout << "  { ";
            for (int s : stateSet) cout << s << " ";
            cout << "} --" << symbol << "--> { ";
            for (int s : nextStateSet) cout << s << " ";
            cout << "}\n";
        }
    }
}
