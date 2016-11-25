#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

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

	private:
		int s;
		int t;
		Piece* grid[8][8];
		sf::RectangleShape* baseGrid[8][8];
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		void initPieces();
		sf::Vector2i convertPointToGrid(sf::Vector2i p);
		sf::Vector2i convertGridToPoint(sf::Vector2i p);
		Piece* heldPiece;
};
#endif