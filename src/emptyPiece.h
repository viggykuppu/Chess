#ifndef CELL_H
#define CELL_H

#include "piece.h"

class EmptyPiece : public Piece {
	public:
		virtual bool isEmpty();
};

#endif