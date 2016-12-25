#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <string>

class Board;

class Piece : public sf::Drawable {
	friend class Board;
	friend class King;
	friend class Pawn;
	
	public:
		enum PieceColor { White, Black};
		Piece(Board& board);
		Piece(Board& board, sf::Vector2i p, PieceColor color);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual void move(sf::Vector2i p);
		virtual bool isEmpty();
		virtual bool canMove(sf::Vector2i p);
		virtual bool getJustDoubleJumped();
		virtual std::vector<sf::Vector2i> getPossibleMoves();
		void setPosition(sf::Vector2i p);
		sf::Vector2i getPosition();
		void setRealPosition(sf::Vector2i p);
		PieceColor getColor();
		int getTurnLastMovedOn();
		bool isValidSpace(sf::Vector2i p);
		

	protected:
		Piece(Board& board, sf::Vector2i p, PieceColor color, std::string pieceMarker);
		PieceColor color;
		sf::Sprite pieceSprite;
		sf::Texture pieceTexture;
		int x,y;
		Board& board;
		bool isBlocked(sf::Vector2i p, bool canCapture);
		std::string pieceMarker;
		void loadPieceTexture();
		int turnLastMovedOn;
		bool hasMoved;

};
#endif