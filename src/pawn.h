#ifndef PAWN_H
#define PAWN_H

#include <SFML/Graphics.hpp>
#include "piece.h"

class Pawn : public Piece {
	public:
		Pawn(Board& board, sf::Vector2i p, PieceColor color);
		virtual void move(sf::Vector2i p);
		virtual bool canMove(sf::Vector2i p);
		bool getJustDoubleJumped();

	private:
		bool hasMoved;
		bool justDoubleJumped;
		bool canEnPassant(sf::Vector2i p);

};

#endif