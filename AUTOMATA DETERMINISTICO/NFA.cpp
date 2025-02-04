#include "NFA.h"

NFA::NFA(int initialState, set<int> finalStates)
    : initialState(initialState), finalStates(finalStates) {}

void NFA::addTransition(int from, char symbol, int to) {
    transitions[from][symbol].insert(to);
}

map<int, map<char, set<int>>> NFA::getTransitions() const {
    return transitions;
}

int NFA::getInitialState() const {
    return initialState;
}

set<int> NFA::getFinalStates() const {
    return finalStates;
}

void NFA::printNFA() const {
    cout << "NFA Transitions:\n";
    for (const auto& [state, transitionMap] : transitions) {
        for (const auto& [symbol, states] : transitionMap) {
            for (int nextState : states) {
                cout << "  (" << state << ") --" << symbol << "--> (" << nextState << ")\n";
            }
        }
    }
}
