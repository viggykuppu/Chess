#include "piece.h"
#include "board.h"
#include <cmath>

Piece::Piece(Board& board):board(board){
}

bool Piece::isEmpty(){
	return false;
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(piece,states);
}

bool Piece::move(sf::Vector2i p){
	return false;
}

bool Piece::isBlocked(sf::Vector2i p, bool canCapture){
	int dy = (p.y-this->y)/std::abs((p.y-this->y));
	int dx = (p.x-this->x)/std::abs((p.x-this->x));
	int n = std::abs(p.y-this->y);
	int currentX = x + dx;
	int currentY = y + dy;
	for(int i = 0; i < n-1; i++){
		if(!this->board.getPiece(sf::Vector2i(currentX,currentY)).isEmpty()){
			return true;
		}
		currentX += dx;
		currentY += dy;
	}
	return true;
}