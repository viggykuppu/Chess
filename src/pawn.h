#ifndef PAWN_H
#define PAWN_H

#include <SFML/Graphics.hpp>
#include "piece.h"

class Pawn : public Piece {
	public:
		Pawn(Board& board, sf::Vector2i p, PieceColor color);
		virtual bool isEmpty();
		virtual void move(sf::Vector2i p);
		virtual bool canMove(sf::Vector2i p);

	private:
		bool hasMoved;

};

#endif