#ifndef QUEEN_H
#define QUEEN_H

#include <SFML/Graphics.hpp>
#include "piece.h"

class Queen : public Piece {
	public:
		Queen(Board& board, sf::Vector2i p, PieceColor color);
		bool canMove(sf::Vector2i p);
};

#endif