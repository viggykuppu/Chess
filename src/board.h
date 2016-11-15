#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

class Piece;

class Board : public sf::Drawable {
	public:
		Board(int s);
		~Board();
		void addPiece(Piece piece);
		Piece getPiece(sf::Vector2i p);

	private:
		int s;
		Piece* grid[8][8];
		sf::RectangleShape* baseGrid[8][8];
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void initPieces();
};
#endif