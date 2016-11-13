#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include "board.h"

class Piece : public sf::Drawable {
	public:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		enum PieceColor { White, Black};
		virtual bool isEmpty()=0;
		virtual bool move(sf::Vector2i p);
		void setPosition(sf::Vector2i p);
		sf::Vector2i getPosition();

	protected:
		PieceColor color;
		sf::RectangleShape piece;
		int x,y;
		Board board;
};
#endif