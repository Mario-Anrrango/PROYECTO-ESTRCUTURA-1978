import graphviz

class Automata:
    def __init__(self, num_states, alphabet):
        self.num_states = num_states
        self.states = set(range(num_states))
        self.alphabet = set(alphabet) | {'E'}  # Incluir epsilon
        self.initial_state = None
        self.final_states = set()
        self.transitions = {state: {symbol: set() for symbol in self.alphabet} for state in self.states}
    
    def set_initial_state(self, state):
        if state in self.states:
            self.initial_state = state
    
    def add_final_state(self, state):
        if state in self.states:
            self.final_states.add(state)
    
    def add_transition(self, from_state, symbol, to_state):
        if from_state in self.states and to_state in self.states and symbol in self.alphabet:
            self.transitions[from_state][symbol].add(to_state)
    
    def epsilon_closure(self, states):
        stack = list(states)
        closure = set(states)
        while stack:
            state = stack.pop()
            for next_state in self.transitions[state].get('ε', []):
                if next_state not in closure:
                    closure.add(next_state)
                    stack.append(next_state)
        return closure

    def convert_to_dfa(self):
        dfa_transitions = {}
        dfa_states = {}
        dfa_final_states = set()
        
        initial_closure = frozenset(self.epsilon_closure({self.initial_state}))
        state_queue = [initial_closure]
        dfa_states[initial_closure] = 0
        new_state_id = 1

        while state_queue:
            current_state = state_queue.pop(0)
            dfa_transitions[current_state] = {}
            
            for symbol in self.alphabet - {'ε'}:
                new_state = set()
                for substate in current_state:
                    new_state.update(self.transitions[substate].get(symbol, []))
                
                new_closure = frozenset(self.epsilon_closure(new_state))
                
                if new_closure not in dfa_states and new_closure:
                    dfa_states[new_closure] = new_state_id
                    new_state_id += 1
                    state_queue.append(new_closure)
                
                dfa_transitions[current_state][symbol] = new_closure
        
        for nfa_state in dfa_states:
            if any(state in self.final_states for state in nfa_state):
                dfa_final_states.add(nfa_state)
        
        return DFA(dfa_states, dfa_transitions, initial_closure, dfa_final_states)
    
    def draw(self, filename="nfa"):  
        dot = graphviz.Digraph()
        for state in self.states:
            shape = "doublecircle" if state in self.final_states else "circle"
            dot.node(str(state), shape=shape)
        for from_state, transitions in self.transitions.items():
            for symbol, to_states in transitions.items():
                for to_state in to_states:
                    dot.edge(str(from_state), str(to_state), label=symbol)
        dot.render(filename, format="png", cleanup=True)

class DFA:
    def __init__(self, states, transitions, initial_state, final_states):
        self.states = states
        self.transitions = transitions
        self.initial_state = initial_state
        self.final_states = final_states
    
    def draw(self, filename="dfa"):
        dot = graphviz.Digraph()
        for state, state_id in self.states.items():
            shape = "doublecircle" if state in self.final_states else "circle"
            dot.node(str(state_id), shape=shape)
        for from_state, transitions in self.transitions.items():
            for symbol, to_state in transitions.items():
                if to_state:
                    dot.edge(str(self.states[from_state]), str(self.states[to_state]), label=symbol)
        dot.render(filename, format="png", cleanup=True)

# INTERFAZ POR CONSOLA
num_states = int(input("Ingrese el número total de estados: "))
alphabet = set(input("Ingrese el alfabeto separado por espacios (incluir 'e' si es necesario): ").split())

automata = Automata(num_states, alphabet)

initial_state = int(input("Ingrese el estado inicial: "))
automata.set_initial_state(initial_state)

num_final_states = int(input("Ingrese la cantidad de estados finales: "))
final_states = list(map(int, input("Ingrese los estados finales separados por espacios: ").split()))
for state in final_states:
    automata.add_final_state(state)

num_transitions = int(input("Ingrese la cantidad de transiciones: "))
print("Ingrese las transiciones en formato: estado_origen símbolo estado_destino")
for _ in range(num_transitions):
    from_state, symbol, to_state = input().split()
    automata.add_transition(int(from_state), symbol, int(to_state))

# Imprimir NFA
print("\n==== NFA ====")
print("NFA Transitions:")
for from_state, transitions in automata.transitions.items():
    for symbol, to_states in transitions.items():
        for to_state in to_states:
            print(f"  ({from_state}) --{symbol}--> ({to_state})")

automata.draw("nfa_graph")

# Convertir a DFA
dfa = automata.convert_to_dfa()

# Imprimir DFA
print("\n==== DFA ====")
print("DFA Transitions:")
for from_state, transitions in dfa.transitions.items():
    for symbol, to_state in transitions.items():
        print(f"  {set(from_state)} --{symbol}--> {set(to_state)}")

dfa.draw("dfa_graph")

print("\nSe han generado los archivos 'nfa_graph.png' y 'dfa_graph.png'.")
