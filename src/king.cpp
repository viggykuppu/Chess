#include "king.h"
#include <iostream>

King::King(Board& board, sf::Vector2i p, PieceColor color):Piece(board,p,color,"k"),hasMoved(false){

}

void King::move(sf::Vector2i p){
	Piece::move(p);
	hasMoved = true;
}

bool King::canMove(sf::Vector2i p){
	int dy = std::abs(p.y - this->getPosition().y);
	int dx = std::abs(p.x - this->getPosition().x);
	if(dx <= 1 && dy <= 1){
		return !isBlocked(p,true);
	}
	
	return false;
}