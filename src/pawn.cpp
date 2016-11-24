#include "pawn.h"

bool Pawn::isEmpty(){
	return false;
}

bool Pawn::move(sf::Vector2i p){

	return false;
}

bool Pawn::canMove(sf::Vector2i p){
	int parity;
	if(this->color == PieceColor::Black){
		parity = -1;
	} else {
		parity = 1;
	}
	int dx = std::abs(p.y - this->getPosition().y);
	int dy = std::abs(p.x - this->getPosition().x);
	return false;
}