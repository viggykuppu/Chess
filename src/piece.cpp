#include "piece.h"
#include "board.h"
#include <cmath>

Piece::Piece(Board& board):board(board){
}

Piece::Piece(Board& board, sf::Vector2i p, PieceColor color):board(board),color(color),x(p.x),y(p.y){
}

bool Piece::isEmpty(){
	return false;
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(piece,states);
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
	if(this->board.getPiece(sf::Vector2i(currentX,currentY)).isEmpty()){
		return false;
	}
	if(canCapture && this->color != board.getPiece(sf::Vector2i(currentX,currentY)).color){
		return false;
	}
	return true;
}

sf::Vector2i Piece::getPosition(){
	return sf::Vector2i(this->x,this->y);
}

void Piece::setPosition(sf::Vector2i p){
	this->x = p.x;
	this->y = p.y;
}

void Piece::move(sf::Vector2i p){
	this->board.placePiece(*this, p);
}

bool Piece::canMove(sf::Vector2i p){
	return false;
}