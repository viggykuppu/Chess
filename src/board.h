#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "piece.h"

class Piece;

class Board : public sf::Drawable {
	public:
		Board(int s);
		~Board();
		void placePiece(Piece& piece, sf::Vector2i p);
		Piece* getPiece(sf::Vector2i p);
		void update();
		void click(int x, int y);
		void unclick(int x, int y);
		void mouseMove(int x, int y);
		int getS();
		int getL();
		void removePiece(sf::Vector2i p);
		int getTurnCount();
		void incrementTurnCount();
		bool inCheck();

	private:
		int s;
		int l;
		int turnCount;
		Piece::PieceColor turn;
		Piece* grid[8][8];
		sf::RectangleShape* baseGrid[8][8];
		Piece* heldPiece;
		Piece* whiteKing;
		Piece* blackKing;
		bool testMoveForCheck(Piece& piece, sf::Vector2i p);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void initPieces();
		sf::Vector2i convertPointToGrid(sf::Vector2i p);
		sf::Vector2i convertGridToPoint(sf::Vector2i p);

};
#endif