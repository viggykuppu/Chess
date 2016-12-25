#include "knight.h"
#include "board.h"

Knight::Knight(Board& board, sf::Vector2i p, PieceColor color):Piece(board,p,color,"n"){

}

bool Knight::canMove(sf::Vector2i p){
	int dy = std::abs(p.y - this->getPosition().y);
	int dx = std::abs(p.x - this->getPosition().x);
	if((dx == 2 && dy == 1) || (dx == 1 && dy == 2)){
		Piece* destinationPiece = this->board.getPiece(p);
		if(destinationPiece->isEmpty() || destinationPiece->getColor() != this->color){
			return true;
		}
	}
	return false;
}