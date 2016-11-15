#include "pawn.h"


bool Pawn::isEmpty(){
	return false;
}

bool Pawn::move(sf::Vector2i p){
	int parity;
	if(this->color == PieceColor::Black){
		parity = -1;
	} else {
		parity = 1;
	}
	return false;
}