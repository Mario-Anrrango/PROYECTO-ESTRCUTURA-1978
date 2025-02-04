#ifndef NFA_H
#define NFA_H

#include <map>
#include <set>
#include <iostream>

using namespace std;

class NFA {
private:
    map<int, map<char, set<int>>> transitions; // Transiciones: estado -> (símbolo -> {estados alcanzables})
    int initialState;
    set<int> finalStates;

public:
    NFA(int initialState, set<int> finalStates);
    void addTransition(int from, char symbol, int to);
    map<int, map<char, set<int>>> getTransitions() const;
    int getInitialState() const;
    set<int> getFinalStates() const;
    void printNFA() const;
};

#endif
