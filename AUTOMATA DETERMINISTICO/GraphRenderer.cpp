#include "GraphRenderer.h"
#include <iostream>
#include <cmath>

GraphRenderer::GraphRenderer(int width, int height, int numStates)
    : window(sf::VideoMode(width, height), "Automata Graph") {
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        std::cerr << "Error: No se pudo cargar la fuente.\n";
    }
    window.setSize(sf::Vector2u(width, height));

    // Distribución circular de los estados
    sf::Vector2f center(width / 2.0f, height / 2.0f);
    float radius = std::min(width, height) / 3.0f;
    for (int i = 0; i < numStates; i++) {
        float angle = 2 * 3.14159265f * i / numStates;
        float x = center.x + radius * std::cos(angle);
        float y = center.y + radius * std::sin(angle);
        statePositions[i] = sf::Vector2f(x, y);
    }
}

void GraphRenderer::drawArrow(sf::Vector2f start, sf::Vector2f end, const std::string& label) {
    // Si es un self-loop (origen igual a destino)
    if (start == end) {
        float loopRadius = 40;
        int numSegments = 30;
        float startAngle = -3.14159265f / 4;
        float endAngle = 3.14159265f / 4;
        sf::Vector2f arcCenter = start + sf::Vector2f(0, -loopRadius);
        sf::VertexArray arc(sf::LinesStrip, numSegments + 1);
        for (int i = 0; i <= numSegments; i++) {
            float angle = startAngle + (endAngle - startAngle) * i / numSegments;
            float x = arcCenter.x + loopRadius * std::cos(angle);
            float y = arcCenter.y + loopRadius * std::sin(angle);
            arc[i] = sf::Vertex(sf::Vector2f(x, y), sf::Color::Black);
        }
        window.draw(arc);

        // Dibujar la cabeza de la flecha al final del arco
        sf::Vector2f p1 = arc[numSegments - 1].position;
        sf::Vector2f p2 = arc[numSegments].position;
        sf::Vector2f dir = p2 - p1;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len != 0) {
            dir /= len;
        }
        sf::Vector2f perp(-dir.y, dir.x);
        float arrowSize = 10;
        sf::VertexArray arrowHead(sf::Triangles, 3);
        arrowHead[0].position = p2;
        arrowHead[0].color = sf::Color::Black;
        arrowHead[1].position = p2 - arrowSize * dir + (arrowSize / 2.f) * perp;
        arrowHead[1].color = sf::Color::Black;
        arrowHead[2].position = p2 - arrowSize * dir - (arrowSize / 2.f) * perp;
        arrowHead[2].color = sf::Color::Black;
        window.draw(arrowHead);

        // Colocar la etiqueta en el centro del arco
        sf::Text text;
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(25);
        text.setFillColor(sf::Color::Red);
        sf::Vector2f mid = arc[numSegments / 2].position;
        mid.y -= 20;
        text.setPosition(mid);
        window.draw(text);
    }
    else {
        // Dibujar una línea recta para transiciones normales
        sf::Vertex line[] = {
            sf::Vertex(start, sf::Color::Black),
            sf::Vertex(end, sf::Color::Black)
        };
        window.draw(line, 2, sf::Lines);

        // Colocar la etiqueta en el punto medio
        sf::Vector2f midpoint = (start + end) / 2.f;
        midpoint.y -= 20;
        sf::Text text;
        text.setFont(font);
        text.setString(label);
        text.setCharacterSize(25);
        text.setFillColor(sf::Color::Red);
        text.setPosition(midpoint);
        window.draw(text);

        // Dibujar la cabeza de la flecha
        sf::Vector2f dir = end - start;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        if (len != 0) {
            dir /= len;
        }
        sf::Vector2f perp(-dir.y, dir.x);
        float arrowSize = 10;
        sf::VertexArray arrowHead(sf::Triangles, 3);
        arrowHead[0].position = end;
        arrowHead[0].color = sf::Color::Black;
        arrowHead[1].position = end - arrowSize * dir + (arrowSize / 2.f) * perp;
        arrowHead[1].color = sf::Color::Black;
        arrowHead[2].position = end - arrowSize * dir - (arrowSize / 2.f) * perp;
        arrowHead[2].color = sf::Color::Black;
        window.draw(arrowHead);
    }
}

void GraphRenderer::drawGraph(const std::vector<Transition>& transitions, const std::set<int>& finalStates) {
    window.clear(sf::Color::White);

    // Dibujar los estados
    for (const auto& [state, pos] : statePositions) {
        sf::CircleShape circle(40);
        circle.setFillColor(sf::Color::Black);
        circle.setPosition(pos - sf::Vector2f(40, 40));

        if (finalStates.count(state)) {
            sf::CircleShape innerCircle(35);
            innerCircle.setFillColor(sf::Color::White);
            innerCircle.setOutlineThickness(2);
            innerCircle.setOutlineColor(sf::Color::Black);
            innerCircle.setPosition(pos - sf::Vector2f(35, 35));
            window.draw(innerCircle);
        }
        window.draw(circle);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(state));
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        sf::FloatRect textBounds = text.getLocalBounds();
        text.setOrigin(textBounds.width / 2, textBounds.height / 2);
        text.setPosition(pos);
        window.draw(text);
    }

    // Agrupar transiciones por par (from, to)
    std::map<std::pair<int, int>, std::string> grouped;
    for (const auto& t : transitions) {
        std::pair<int, int> key = { t.from, t.to };
        if (grouped.find(key) == grouped.end()) {
            grouped[key] = std::string(1, t.symbol);
        } else {
            grouped[key] += ", " + std::string(1, t.symbol);
        }
    }

    // Dibujar las transiciones agrupadas
    for (const auto& [key, label] : grouped) {
        int from = key.first;
        int to = key.second;
        // Se asume que cada estado tiene posición definida en statePositions
        sf::Vector2f start = statePositions[from];
        sf::Vector2f end = statePositions[to];
        drawArrow(start, end, label);
    }

    window.display();
}

void GraphRenderer::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}
