#ifndef CELL_H
#define CELL_H

#include "piece.h"
#include "board.h"

class EmptyPiece : public Piece {
	public:
		EmptyPiece(Board& board);
		virtual bool isEmpty();
};

#endif