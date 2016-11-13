#include "board.h"

Board::Board(int s){
	this->s = s;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			int size = s/8;
			sf::RectangleShape* rectangle = new sf::RectangleShape(sf::Vector2f(size,size));
			rectangle->setPosition(sf::Vector2f(i*size,j*size));
			if((i + j)%2 == 0){
				rectangle->setFillColor(sf::Color::Black);
			} else {
				rectangle->setFillColor(sf::Color::White);
			}
			
			this->baseGrid[i][j] = rectangle;
		}
	}
}

void Board::initPieces(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			this->grid[i][j] = new EmptyPiece();
		}
	}
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			target.draw(*baseGrid[i][j]);
		}
	}
}