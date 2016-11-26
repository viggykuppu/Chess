#ifndef KNIGHT_H
#define KNIGHT_H

#include <SFML/Graphics.hpp>
#include "piece.h"

class Knight : public Piece {
	public:
		Knight(Board& board, sf::Vector2i p, PieceColor color);
		bool canMove(sf::Vector2i p);
};

#endif