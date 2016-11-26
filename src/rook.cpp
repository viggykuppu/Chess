#include "rook.h"
#include <cmath>
#include <iostream>

Rook::Rook(Board& board, sf::Vector2i p, PieceColor color):Piece(board,p,color,"r"){

}

bool Rook::canMove(sf::Vector2i p){
	int dy = std::abs(p.y - this->getPosition().y);
	int dx = std::abs(p.x - this->getPosition().x);
	if(dx*dy == 0){
		return !isBlocked(p,true);
	}
	std::cout << "prod not 0" << std::endl;
	return false;
}