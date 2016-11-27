#include "piece.h"
#include "board.h"
#include <cmath>
#include <iostream>

Piece::Piece(Board& board):board(board){
}

Piece::Piece(Board& board, sf::Vector2i p, PieceColor color):Piece(board,p,color,""){

}

Piece::Piece(Board& board, sf::Vector2i p, PieceColor color, std::string pieceMarker):pieceMarker(pieceMarker),board(board),color(color),turnLastMovedOn(-1),hasMoved(false){
	this->setPosition(p);
	if(!isEmpty()){
		loadPieceTexture();
	}
}

bool Piece::isEmpty(){
	return false;
}

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(pieceSprite,states);
}

bool Piece::isBlocked(sf::Vector2i p, bool canCapture){
	int dy = p.y-this->y == 0 ? 0 : (p.y-this->y)/std::abs((p.y-this->y));
	int dx = p.x-this->x == 0 ? 0 : (p.x-this->x)/std::abs((p.x-this->x));
	int n = dy == 0 ? std::abs(p.x-this->x) : std::abs(p.y-this->y);
	int currentX = x + dx;
	int currentY = y + dy;
	for(int i = 0; i < n-1; i++){
		if(!this->board.getPiece(sf::Vector2i(currentX,currentY))->isEmpty()){
			return true;
		}
		currentX += dx;
		currentY += dy;
	}

	if(this->board.getPiece(sf::Vector2i(currentX,currentY))->isEmpty()){
		return false;
	}
	if(canCapture && this->color != board.getPiece(sf::Vector2i(currentX,currentY))->color){
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
	this->pieceSprite.setPosition(p.x*this->board.getL(),p.y*this->board.getL());
}

void Piece::setRealPosition(sf::Vector2i p){
	this->pieceSprite.setPosition(p.x-this->board.getL()/2,p.y-this->board.getL()/2);
}

void Piece::move(sf::Vector2i p){
	this->turnLastMovedOn = this->board.getTurnCount();
	this->board.placePiece(*this, p);
	this->board.incrementTurnCount();
	this->hasMoved = false;
}

bool Piece::canMove(sf::Vector2i p){
	return false;
}

void Piece::loadPieceTexture(){
	if(this->color == PieceColor::Black){
		if(!this->pieceTexture.loadFromFile("img/Chess_"+pieceMarker+"dt45.png")){
			//error loading
		}
	} else {
		if(!this->pieceTexture.loadFromFile("img/Chess_"+pieceMarker+"lt45.png")){
			//error loading
		}
	}
	this->pieceTexture.setSmooth(true);
	this->pieceSprite.setTexture(pieceTexture);
	float scaleFactor = float(this->board.getL())/2000;
	this->pieceSprite.setScale(scaleFactor,scaleFactor);
}

Piece::PieceColor Piece::getColor(){
	return this->color;
}

bool Piece::getJustDoubleJumped(){
	return false;
}

int Piece::getTurnLastMovedOn(){
	return this->turnLastMovedOn;
}