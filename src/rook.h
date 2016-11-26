#ifndef ROOK_H
#define ROOK_H

#include <SFML/Graphics.hpp>
#include "piece.h"

class Rook : public Piece {
	public:
		Rook(Board& board, sf::Vector2i p, PieceColor color);
		virtual bool canMove(sf::Vector2i p);

};

#endif