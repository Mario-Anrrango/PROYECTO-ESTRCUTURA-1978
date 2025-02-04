#ifndef DFA_H
#define DFA_H

#include <map>
#include <set>
#include <iostream>

using namespace std;

class DFA {
private:
    map<set<int>, map<char, set<int>>> transitions;
    set<set<int>> states;
    set<int> finalStates;

public:
    void addTransition(set<int> from, char symbol, set<int> to);
    void addState(set<int> state);
    void addFinalState(int state);
    void printDFA() const;
};

#endif
