#include "king.h"
#include "board.h"
#include <iostream>

King::King(Board& board, sf::Vector2i p, PieceColor color):Piece(board,p,color,"k"){

}

bool King::canMove(sf::Vector2i p){
	int dy = std::abs(p.y - this->getPosition().y);
	int dx = std::abs(p.x - this->getPosition().x);
	if(!this->hasMoved && this->canCastle(this,p)){
		return true;
	}
	if(dx <= 1 && dy <= 1){
		return !isBlocked(p,true);
	}
	
	return false;
}

bool King::canCastle(Piece* piece, sf::Vector2i p){
	int dx = p.x - piece->getPosition().x;
	int dy = std::abs(p.y - piece->getPosition().y);
	Piece* rook;
	sf::Vector2i finalRookPosition;
	if(dy == 0 && std::abs(dx) == 2){
		if(dx < 0){
			rook = board.grid[p.y][0];
			finalRookPosition = sf::Vector2i(3,p.y);
		} else {
			rook = board.grid[p.y][7];
			finalRookPosition = sf::Vector2i(5,p.y);
		}
		if(!rook->isEmpty() && rook->pieceMarker == "r"){
			int ix = dx/std::abs(dx);
			if(!rook->hasMoved && !rook->isBlocked(finalRookPosition,false) && !board.testMoveForCheck(*piece, sf::Vector2i(piece->getPosition().x+ix,p.y)) && !board.testMoveForCheck(*piece, sf::Vector2i(piece->getPosition().x+2*ix,p.y))){
				rook->move(finalRookPosition);
				board.decrementTurnCount();
				return true;
			}
		}
	}
	return false;
}