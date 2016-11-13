#include <SFML/Graphics.hpp>
#include "board.h"

int main()
{
    int x = 800;
    int y = 800;
    sf::RenderWindow window(sf::VideoMode(x, y), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    Board board(800);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(board);
        window.display();
    }

    return 0;
}