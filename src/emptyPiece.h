#ifndef CELL_H
#define CELL_H

#include "piece.h"

class Board;

class EmptyPiece : public Piece {
	public:
		EmptyPiece(Board& board);
		virtual bool isEmpty();
};

#endif