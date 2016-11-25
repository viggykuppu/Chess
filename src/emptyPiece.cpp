#include "emptyPiece.h"


EmptyPiece::EmptyPiece(Board& board,sf::Vector2i p):Piece(board){
	this->setPosition(p);
}

bool EmptyPiece::isEmpty(){
	return true;
}