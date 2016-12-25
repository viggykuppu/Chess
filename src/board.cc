#include "board.h"
#include "emptyPiece.h"
#include "pawn.h"
#include "piece.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "king.h"
#include "queen.h"
#include <iostream>

Board::Board(int s):s(s),turn(Piece::PieceColor::White),turnCount(0){
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
	this->heldPiece = nullptr;
	this->heldPieceMovesEvaluated = false;
}

Board::~Board(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			delete this->baseGrid[i][j];
			delete this->grid[i][j];
		}
	}
	this->whiteKing = nullptr;
	this->blackKing = nullptr;
	this->heldPiece = nullptr;
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
	//Empty Pieces
	for(int i = 2; i < 6; i++){
		for(int j = 0; j < 8; j++){
			this->grid[i][j] = new EmptyPiece(*this, sf::Vector2i(i,j));
		}  
	}

	//Pawns
	for(int i = 0; i < 8; i++){
		this->grid[1][i] = new Pawn(*this, sf::Vector2i(i,1), Piece::PieceColor::Black);
		this->grid[6][i] = new Pawn(*this, sf::Vector2i(i,6), Piece::PieceColor::White);
	}

	//Rooks 
	this->grid[0][0] = new Rook(*this, sf::Vector2i(0,0), Piece::PieceColor::Black);
	this->grid[0][7] = new Rook(*this, sf::Vector2i(7,0), Piece::PieceColor::Black);
	this->grid[7][0] = new Rook(*this, sf::Vector2i(0,7), Piece::PieceColor::White);
	this->grid[7][7] = new Rook(*this, sf::Vector2i(7,7), Piece::PieceColor::White);

	//Bishops
	this->grid[0][1] = new Bishop(*this, sf::Vector2i(1,0), Piece::PieceColor::Black);
	this->grid[0][6] = new Bishop(*this, sf::Vector2i(6,0), Piece::PieceColor::Black);
	this->grid[7][1] = new Bishop(*this, sf::Vector2i(1,7), Piece::PieceColor::White);
	this->grid[7][6] = new Bishop(*this, sf::Vector2i(6,7), Piece::PieceColor::White);

	//Knights
	this->grid[0][2] = new Knight(*this, sf::Vector2i(2,0), Piece::PieceColor::Black);
	this->grid[0][5] = new Knight(*this, sf::Vector2i(5,0), Piece::PieceColor::Black);
	this->grid[7][2] = new Knight(*this, sf::Vector2i(2,7), Piece::PieceColor::White);
	this->grid[7][5] = new Knight(*this, sf::Vector2i(5,7), Piece::PieceColor::White);

	//Queens
	this->grid[0][3] = new Queen(*this, sf::Vector2i(3,0), Piece::PieceColor::Black);
	this->grid[7][3] = new Queen(*this, sf::Vector2i(3,7), Piece::PieceColor::White);

	//Kings
	this->grid[0][4] = new King(*this, sf::Vector2i(4,0), Piece::PieceColor::Black);
	this->grid[7][4] = new King(*this, sf::Vector2i(4,7), Piece::PieceColor::White);
	this->blackKing = this->grid[0][4];
	this->whiteKing = this->grid[7][4];
}

void Board::highlightSquares(std::vector<sf::Vector2i> squares){
	for(const sf::Vector2i& p : this->currentPossibleMoves){
		if( (p.x + p.y) % 2 == 0){
			this->baseGrid[p.x][p.y]->setFillColor(sf::Color(255, 255, 20));
		} else {
			this->baseGrid[p.x][p.y]->setFillColor(sf::Color(180, 180, 20));
		}
	}
}

void Board::resetSquareColors(std::vector<sf::Vector2i> squares){
	for(const sf::Vector2i& p : this->currentPossibleMoves){
		if( (p.x + p.y) % 2 == 0){
			this->baseGrid[p.x][p.y]->setFillColor(sf::Color::White);
		} else {
			this->baseGrid[p.x][p.y]->setFillColor(sf::Color(180,180,180));
		}
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
	if(this->turn == heldPiece->getColor()){
		if(heldPiece->canMove(p) && (p.x != heldPiece->getPosition().x || p.y != heldPiece->getPosition().y) && !testMoveForCheck(*heldPiece,p)){
			heldPiece->move(p);
			if(this->turn == Piece::PieceColor::Black){
				this->turn = Piece::PieceColor::White;
			} else {
				this->turn = Piece::PieceColor::Black;
			}
		} else {
			this->heldPiece->setPosition(this->heldPiece->getPosition());
		}
	}
	this->heldPiece = nullptr;
	this->resetSquareColors(this->currentPossibleMoves);
	this->currentPossibleMoves.clear();
	this->heldPieceMovesEvaluated = false;
}

void Board::mouseMove(int x, int y){
	if(this->heldPiece != nullptr && this->heldPiece->getColor() == turn){
		this->heldPiece->setRealPosition(sf::Vector2i(x,y));
		if(!this->heldPieceMovesEvaluated){
			this->currentPossibleMoves = this->heldPiece->getPossibleMoves();
			std::cout << this->currentPossibleMoves.size() << std::endl;
			this->highlightSquares(this->currentPossibleMoves);
			this->heldPieceMovesEvaluated = true;
		}
	}
}

sf::Vector2i Board::convertPointToGrid(sf::Vector2i p){
	return sf::Vector2i(p.x/l,p.y/l);
}

sf::Vector2i Board::convertGridToPoint(sf::Vector2i p){
	return sf::Vector2i(p.x*l,p.y*l);
}

void Board::removePiece(sf::Vector2i p){
	Piece* emptyPiece = new EmptyPiece(*this,p);
	this->placePiece(*emptyPiece, p);
}

int Board::getTurnCount(){
	return turnCount;
}

void Board::incrementTurnCount(){
	turnCount = turnCount + 1;
}

void Board::decrementTurnCount(){
	turnCount = turnCount - 1;
}

bool Board::inCheck(Piece::PieceColor kingColor){
	sf::Vector2i kingPosition;
	Piece::PieceColor enemyColor;
	if(kingColor == Piece::PieceColor::White){
		kingPosition = whiteKing->getPosition();
		enemyColor = Piece::PieceColor::Black;
	} else {
		kingPosition = blackKing->getPosition();
		enemyColor = Piece::PieceColor::White;
	}
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			Piece* piece = this->grid[i][j];
			if(!piece->isEmpty() && piece->getColor() != this->turn && piece->pieceMarker != "k"){
				if(piece->canMove(kingPosition)){
					return true;
				}
			}
		}
	}
	//Check for Knights
	// std::vector<int> xOffsets = {1,-1,2,-2};
	// std::vector<int> yOffsets = {2,-2,1,-1};
	// for(int i = 0; i < 4; i++){
	// 	for(int j = 0; j < 2; j++){
	// 		int offset = i > 1 ? 2 : 0;
	// 		sf::Vector2i currentPosition = sf::Vector2i(kingPosition.x+xOffsets[i],kingPosition.y+yOffsets[j+offset]);
	// 		if(isValidSpace(currentPosition) && checkSpaceForPieces(currentPosition,{"n"},enemyColor)){
	// 			return true;
	// 		}
	// 	}
	// }
	// //Check upwards
	// sf::Vector2i currentPosition = sf::Vector2i(kingPosition.x,kingPosition.y);
	// for(int i = 0; i < 8; i++){
	// 	sf::Vector2i currentPosition = sf::Vector2i(currentPosition.x,currentPosition.y+1);
	// 	if(isValidSpace(currentPosition)){
	// 		Piece* currentPiece = this->getPiece(currentPosition);
	// 		if(currentPiece->getColor() == kingColor){
	// 			break;
	// 		}
	// 		if(currentPiece->isEmpty()){
	// 			continue;
	// 		}
	// 		if(checkSpaceForPieces(currentPosition, {"q","r"}, enemyColor)){
	// 			return true;
	// 		}
	// 	} else {
	// 		break;
	// 	}
	// }
	return false;
}

bool Board::checkSpaceForPieces(sf::Vector2i p, std::vector<std::string> pieces, Piece::PieceColor color){
	for(std::vector<std::string>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
	    return *it == this->getPiece(p)->pieceMarker && this->getPiece(p)->getColor() == color;
	}
	return false;
}

bool Board::isValidSpace(sf::Vector2i p){
	return !(p.x < 0 || p.x > 7 || p.y < 0 || p.y > 7);
}

bool Board::testMoveForCheck(Piece& piece, sf::Vector2i p){
	Piece* end = grid[p.y][p.x];
	sf::Vector2i q = piece.getPosition();

	piece.setPosition(p);

	grid[p.y][p.x] = &piece;
	grid[q.y][q.x] = new EmptyPiece(*this,q);

	bool retVal = inCheck(turn);

	delete grid[q.y][q.x];

	piece.setPosition(q);

	grid[q.y][q.x] = &piece;
	grid[p.y][p.x] = end;
	
	return retVal;
}