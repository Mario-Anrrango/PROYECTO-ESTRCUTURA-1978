#ifndef GRAPHRENDER_H
#define GRAPHRENDER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <cmath>

struct Transition {
    int from;
    int to;
    char symbol;
};

class GraphRenderer {
public:
    // Constructor que recibe el número de estados para posicionarlos dinámicamente
    GraphRenderer(int width, int height, int numStates);
    // Ahora drawArrow recibe una cadena de texto con la(s) etiqueta(s)
    void drawArrow(sf::Vector2f start, sf::Vector2f end, const std::string& label);
    void drawGraph(const std::vector<Transition>& transitions, const std::set<int>& finalStates);
    void run();

private:
    sf::RenderWindow window;
    sf::Font font;
    std::map<int, sf::Vector2f> statePositions;
};

#endif // GRAPHRENDER_H
