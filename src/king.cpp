#include "king.h"
#include "board.h"
#include <iostream>

King::King(Board& board, sf::Vector2i p, PieceColor color):Piece(board,p,color,"k"){

}

bool King::canMove(sf::Vector2i p){
	int dy = std::abs(p.y - this->getPosition().y);
	int dx = std::abs(p.x - this->getPosition().x);
	if(!this->hasMoved && this->board.canCastle(this,p)){
		return true;
	}
	if(dx <= 1 && dy <= 1){
		return !isBlocked(p,true);
	}
	
	return false;
}