#ifndef PAWN_H
#define PAWN_H

#include <SFML/Graphics.hpp>
#include "piece.h"


class Pawn : public Piece {
	public:
		virtual bool isEmpty();
		virtual bool move(sf::Vector2i p);

	private:

};

#endif