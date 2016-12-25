#include <SFML/Graphics.hpp>
#include "board.h"
#include <iostream>

void draw(sf::RenderWindow& window, Board& board);
void update(sf::RenderWindow& window, Board& board);

int main()
{
    int s = 1600;

    sf::RenderWindow window(sf::VideoMode(s, s), "Chess", sf::Style::Close);
    Board board(s);

    while (window.isOpen())
    {
        sf::Clock clock;

        update(window,board);

        draw(window,board);

        sf::Time elapsed = clock.getElapsedTime();
        if (elapsed.asMicroseconds() < 1000000.0 / 60.0) {
            sf::sleep(sf::microseconds(1000000 / 60 - elapsed.asMicroseconds()));
        }
    }

    return 0;
}

void draw(sf::RenderWindow& window, Board& board){
    window.clear();
    window.draw(board);
    window.display();
}

void update(sf::RenderWindow& window, Board& board){
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed){
            window.close();
        } else if(event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left){
            board.click(event.mouseButton.x,event.mouseButton.y);
        } else if(event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left){
            board.unclick(event.mouseButton.x,event.mouseButton.y);
        } else if(event.type == sf::Event::MouseMoved){
            board.mouseMove(event.mouseMove.x,event.mouseMove.y);
        }
    }
}