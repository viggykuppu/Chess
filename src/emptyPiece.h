#ifndef CELL_H
#define CELL_H

#include "piece.h"

class Board;

class EmptyPiece : public Piece {
	public:
		EmptyPiece(Board& board,sf::Vector2i p);
		virtual bool isEmpty();
};

#endif