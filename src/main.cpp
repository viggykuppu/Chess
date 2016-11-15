#include <SFML/Graphics.hpp>
#include "board.h"

int main()
{
    int s = 1600;
    sf::RenderWindow window(sf::VideoMode(s, s), "Chess");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    Board board(s);

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