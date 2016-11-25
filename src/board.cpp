#include "board.h"
#include "emptyPiece.h"
#include "pawn.h"
#include "piece.h"
#include <iostream>

Board::Board(int s):s(s),turn(Piece::PieceColor::White){
	this->l = s/8;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			int size = s/8;
			sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(size,size));
			rectangle->setPosition(sf::Vector2f(i*size,j*size));
			if((i + j)%2 == 0){
				rectangle->setFillColor(sf::Color::White);
			} else {
				rectangle->setFillColor(sf::Color(180,180,180));
			}
			
			this->baseGrid[i][j] = rectangle;
		}
	}
	this->initPieces();
}

Board::~Board(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			delete this->baseGrid[i][j];
			delete this->grid[i][j];
		}
	}
}

int Board::getS(){
	return s;
}

int Board::getL(){
	return l;
}

Piece* Board::getPiece(sf::Vector2i p){
	return grid[p.y][p.x];
}

void Board::initPieces(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(i != 1 || i != 6){
				this->grid[i][j] = new EmptyPiece(*this, sf::Vector2i(i,j));
			}
		}  
	}
	for(int i = 0; i < 8; i++){
		this->grid[1][i] = new Pawn(*this, sf::Vector2i(i,1), Piece::PieceColor::Black);
		this->grid[6][i] = new Pawn(*this, sf::Vector2i(i,6), Piece::PieceColor::White);
	}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			target.draw(*baseGrid[i][j]);
		}
	}
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(!grid[i][j]->isEmpty()){
				target.draw(*grid[i][j]);
			}
		}
	}
}

void Board::update(){

}

void Board::placePiece(Piece& piece,sf::Vector2i p){
	delete grid[p.y][p.x];
	sf::Vector2i q = piece.getPosition();
	piece.setPosition(p);
	grid[p.y][p.x] = &piece;
	grid[q.y][q.x] = new EmptyPiece(*this,q);
}

void Board::click(int x, int y){
	sf::Vector2i p = convertPointToGrid(sf::Vector2i(x,y));
	heldPiece = this->grid[p.y][p.x];
}

void Board::unclick(int x, int y){
	sf::Vector2i p = convertPointToGrid(sf::Vector2i(x/l*l,y/l*l));
	if((p.x != heldPiece->getPosition().x || p.y != heldPiece->getPosition().y) && this->turn == heldPiece->getColor()){
		if(heldPiece->canMove(p)){
			std::cout << "moved" << std::endl;
			heldPiece->move(p);
			if(this->turn == Piece::PieceColor::Black){
				this->turn = Piece::PieceColor::White;
			} else {
				this->turn = Piece::PieceColor::Black;
			}
		} else {
			std::cout << "no move for you" << std::endl;
		}
	}
}

sf::Vector2i Board::convertPointToGrid(sf::Vector2i p){
	return sf::Vector2i(p.x/l,p.y/l);
}

sf::Vector2i Board::convertGridToPoint(sf::Vector2i p){
	return sf::Vector2i(p.x*l,p.y*l);
}