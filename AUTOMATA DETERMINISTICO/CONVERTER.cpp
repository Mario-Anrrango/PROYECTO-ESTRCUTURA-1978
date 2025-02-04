#include "Converter.h"

DFA Converter::convert(const NFA& nfa, const set<char>& alphabet) {
    DFA dfa;
    queue<set<int>> stateQueue;
    map<set<int>, int> stateMapping;
    int nextState = 0;

    set<int> startState = {nfa.getInitialState()};
    stateQueue.push(startState);
    dfa.addState(startState);
    stateMapping[startState] = nextState++;

    while (!stateQueue.empty()) {
        set<int> currentState = stateQueue.front();
        stateQueue.pop();

        for (char symbol : alphabet) {
            set<int> newState;

            for (int state : currentState) {
                auto transitions = nfa.getTransitions();
                if (transitions.count(state) && transitions[state].count(symbol)) {
                    newState.insert(transitions[state][symbol].begin(), transitions[state][symbol].end());
                }
            }

            if (!newState.empty()) {
                if (stateMapping.find(newState) == stateMapping.end()) {
                    dfa.addState(newState);
                    stateQueue.push(newState);
                    stateMapping[newState] = nextState++;
                }
                dfa.addTransition(currentState, symbol, newState);
            }
        }
    }

    for (const auto& [dfaState, _] : stateMapping) {
        for (int s : dfaState) {
            if (nfa.getFinalStates().count(s)) {
                dfa.addFinalState(s);
                break;
            }
        }
    }

    return dfa;
}

