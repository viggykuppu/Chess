#include "emptyPiece.h"


EmptyPiece::EmptyPiece(Board& board):Piece(board){
}

bool EmptyPiece::isEmpty(){
	return true;
}