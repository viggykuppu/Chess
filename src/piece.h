#ifndef PIECE_H
#define PIECE_H

#include <SFML/Graphics.hpp>
#include <string>

class Board;

class Piece : public sf::Drawable {
	public:
		enum PieceColor { White, Black};
		Piece(Board& board);
		Piece(Board& board, sf::Vector2i p, PieceColor color);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		virtual bool isEmpty();
		virtual void move(sf::Vector2i p);
		virtual bool canMove(sf::Vector2i p);
		void setPosition(sf::Vector2i p);
		sf::Vector2i getPosition();
		void setRealPosition(sf::Vector2i p);
		PieceColor getColor();

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

};
#endif