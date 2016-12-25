#include "pawn.h"
#include "board.h"
#include <iostream>

Pawn::Pawn(Board& board,  sf::Vector2i p, PieceColor color):Piece(board,p,color,"p"),justDoubleJumped(false){

}

void Pawn::move(sf::Vector2i p){
	int dy = std::abs(p.y - this->getPosition().y);
	if(dy == 2){
		justDoubleJumped = true;
	} else if(justDoubleJumped){
		justDoubleJumped = false;
	}
	Piece::move(p);
}

bool Pawn::canMove(sf::Vector2i p){
	int parity;
	if(this->color == PieceColor::Black){
		parity = 1;
	} else {
		parity = -1;
	}
	int dy = p.y - this->getPosition().y;
	int dx = p.x - this->getPosition().x;
	if(dy*parity <= 0){
		return false;
	}
	dy = std::abs(dy);
	dx = std::abs(dx);
	int maxDy = hasMoved ? 1 : 2;
	if(dy > maxDy || dx > 1){
		return false;
	}
	if(dx == 0){
		return !isBlocked(p,false);
	} else {
		return (isBlocked(p,false) && !isBlocked(p,true)) || canEnPassant(p);
	}

	return false;
}

std::vector<sf::Vector2i> Pawn::getPossibleMoves(){
	int parity;
	std::vector<sf::Vector2i> possibleMoves;
	if(this->getColor() == PieceColor::Black){
		parity = 1;
	} else {
		parity = -1;
	}
	sf::Vector2i checkPosition = sf::Vector2i(this->getPosition().x,this->getPosition().y+parity);
	if(!board.testMoveForCheck(*this,checkPosition) && board.getPiece(checkPosition)->isEmpty()){
		possibleMoves.push_back(checkPosition);
		checkPosition = checkPosition + sf::Vector2i(0,parity);
		if(!board.testMoveForCheck(*this,checkPosition) && !this->hasMoved && board.getPiece(checkPosition)->isEmpty()){
			possibleMoves.push_back(checkPosition);
		}
	}
	checkPosition = sf::Vector2i(this->getPosition().x+1,this->getPosition().y+parity);
	if(!board.testMoveForCheck(*this,checkPosition) && ((!board.getPiece(checkPosition)->isEmpty() && board.getPiece(checkPosition)->getColor() != this->getColor()) || canEnPassant(checkPosition))){
		possibleMoves.push_back(checkPosition);
		checkPosition = checkPosition + sf::Vector2i(-2,0);
		if(!board.testMoveForCheck(*this,checkPosition) && ((!board.getPiece(checkPosition)->isEmpty() && board.getPiece(checkPosition)->getColor() != this->getColor()) || canEnPassant(checkPosition))){
			possibleMoves.push_back(checkPosition);
		}
	}
	return possibleMoves;
}

bool Pawn::getJustDoubleJumped(){
	return this->justDoubleJumped;
}

bool Pawn::canEnPassant(sf::Vector2i p){
	int dy = p.y - this->getPosition().y;
	int dx = p.x - this->getPosition().x;
	sf::Vector2i checkLocation = sf::Vector2i(p.x,p.y-dy);
	if(this->board.getPiece(checkLocation)->getJustDoubleJumped() && this->board.getTurnCount() - 1 == this->board.getPiece(checkLocation)->getTurnLastMovedOn()){
		this->board.removePiece(checkLocation);
		return true;
	}
	return false;
}