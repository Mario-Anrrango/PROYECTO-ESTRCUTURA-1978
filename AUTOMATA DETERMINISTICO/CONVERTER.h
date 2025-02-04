#ifndef CONVERTER_H
#define CONVERTER_H

#include "NFA.h"
#include "DFA.h"
#include <queue>

class Converter {
public:
    static DFA convert(const NFA& nfa, const set<char>& alphabet);
};

#endif
