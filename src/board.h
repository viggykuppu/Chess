#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "piece.h"
#include "emptyPiece.h"

class Board : public sf::Drawable {
	public:
		Board(int s);
		void addPiece(Piece piece);

	private:
		int s;
		Piece* grid[8][8];
		sf::RectangleShape* baseGrid[8][8];
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void initPieces();
};
#endif