#include "queen.h"

Queen::Queen(Board& board, sf::Vector2i p, PieceColor color):Piece(board,p,color,"q"){

}

bool Queen::canMove(sf::Vector2i p){
	int dy = std::abs(p.y - this->getPosition().y);
	int dx = std::abs(p.x - this->getPosition().x);
	if(dy*dx != 0 && dx == dy){
		return !isBlocked(p,true);
	}
	if(dy*dx == 0){
		return !isBlocked(p,true);
	}
	return false;
}