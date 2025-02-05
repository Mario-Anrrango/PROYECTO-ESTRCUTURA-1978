#ifndef DFA_H
#define DFA_H

#include <iostream>
#include <set>
#include <map>

using namespace std;

class DFA {
private:
    set<set<int>> states;
    map<set<int>, map<char, set<int>>> transitions;
    set<int> finalStates;

public:
    void addTransition(set<int> from, char symbol, set<int> to);
    void addState(set<int> state);
    void addFinalState(int state);
    void printDFA() const;

    // Getters
    const set<set<int>>& getStates() const { return states; }
    const map<set<int>, map<char, set<int>>>& getTransitions() const { return transitions; }
    const set<int>& getFinalStates() const { return finalStates; }
};

#endif
