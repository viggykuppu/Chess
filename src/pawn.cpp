#include "pawn.h"
#include <iostream>

Pawn::Pawn(Board& board,  sf::Vector2i p, PieceColor color):Piece(board,p,color,"p"){
	
}

bool Pawn::isEmpty(){
	return false;
}

void Pawn::move(sf::Vector2i p){
	hasMoved = true;
	Piece::move(p);
}

bool Pawn::canMove(sf::Vector2i p){
	int parity;
	if(this->color == PieceColor::Black){
		parity = 1;
	} else {
		parity = -1;
	}
	int dy = p.y - this->getPosition().y;
	int dx = p.x - this->getPosition().x;
	if(dy*parity <= 0){
		return false;
	}
	dy = std::abs(dy);
	dx = std::abs(dx);
	int maxDy = hasMoved ? 1 : 2;
	if(dy > maxDy || dx > 1){
		std::cout << "lost in ds" << std::endl;
		return false;
	}
	std::cout << dx << ", " << dy << std::endl;
	if(dx == 0){
		return isBlocked(p,false);
	} else {
		return false;
	}

	return false;
}