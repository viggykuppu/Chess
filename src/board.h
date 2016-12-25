#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include "piece.h"

class Piece;

class Board : public sf::Drawable {
	friend class King;

	public:
		Board(int s);
		~Board();
		void placePiece(Piece& piece, sf::Vector2i p);
		Piece* getPiece(sf::Vector2i p);
		void click(int x, int y);
		void unclick(int x, int y);
		void mouseMove(int x, int y);
		int getS();
		int getL();
		void removePiece(sf::Vector2i p);
		int getTurnCount();
		void incrementTurnCount();
		void decrementTurnCount();
		bool inCheck(Piece::PieceColor kingColor);
		bool isCheckMate(Piece::PieceColor kingColor);
		bool isValidSpace(sf::Vector2i p);
		bool testMoveForCheck(Piece& piece, sf::Vector2i p);

	private:
		int s;
		int l;
		int turnCount;
		Piece::PieceColor turn;
		Piece* grid[8][8];
		sf::RectangleShape* baseGrid[8][8];
		Piece* heldPiece;
		std::vector<sf::Vector2i> currentPossibleMoves;
		bool heldPieceMovesEvaluated;
		Piece* whiteKing;
		Piece* blackKing;
		bool checkSpaceForPieces(sf::Vector2i p, std::vector<std::string> pieces, Piece::PieceColor color);
		void initPieces();
		void highlightSquares(std::vector<sf::Vector2i> squares);
		void resetSquareColors(std::vector<sf::Vector2i> squares);
		sf::Vector2i convertPointToGrid(sf::Vector2i p);
		sf::Vector2i convertGridToPoint(sf::Vector2i p);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};
#endif