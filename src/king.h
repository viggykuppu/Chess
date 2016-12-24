#ifndef KING_H
#define KING_H

#include <SFML/Graphics.hpp>
#include "piece.h"

class King : public Piece{
	public:
		King(Board& board, sf::Vector2i p, PieceColor color);
		bool canMove(sf::Vector2i p);

	private:
		bool canCastle(Piece* piece, sf::Vector2i p);
};

#endif