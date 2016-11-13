#include "Piece.h"

void Piece::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(piece,states);
}

bool Piece::move(sf::Vector2i p){
	return false;
}