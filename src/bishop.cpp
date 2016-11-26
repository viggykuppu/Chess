#include "bishop.h"

Bishop::Bishop(Board& board, sf::Vector2i p, PieceColor color):Piece(board,p,color,"b"){

}

bool Bishop::canMove(sf::Vector2i p){
	int dy = std::abs(p.y - this->getPosition().y);
	int dx = std::abs(p.x - this->getPosition().x);
	if(dy == dx){
		return !isBlocked(p,true);
	}
	return false;
}