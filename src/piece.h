#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>

class Board;

class Piece : public sf::Drawable {
	public:
		enum PieceColor { White, Black};
		Piece(Board& board);
		Piece(Board& board, PieceColor color);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual bool isEmpty();
		virtual bool move(sf::Vector2i p);
		virtual bool canMove(sf::Vector2i p);
		void setPosition(sf::Vector2i p);
		sf::Vector2i getPosition();

	protected:
		PieceColor color;
		sf::RectangleShape piece;
		int x,y;
		Board& board;
		bool isBlocked(sf::Vector2i p, bool canCapture);
		int getParity();
};
#endif