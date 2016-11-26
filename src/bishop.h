#ifndef BISOHP_H
#define BISOHP_H

#include <SFML/Graphics.hpp>
#include "piece.h"

class Bishop : public Piece {
	public:
		Bishop(Board& board, sf::Vector2i p, PieceColor color);
		virtual bool canMove(sf::Vector2i p);
};

#endif