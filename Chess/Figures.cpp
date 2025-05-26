#include "Figures.h"
// ChessPiece

ChessPiece::ChessPiece(string color, pair<letterPosition, int> pos, char symbol) {
	Color = color;
	position = pos;
	Symbol = symbol;
}

string ChessPiece::getColor() { return Color; }

pair<letterPosition, int> ChessPiece::getPosition(){ return position; }

char ChessPiece::getSymbol() { return Symbol; }

void ChessPiece::setPosition(pair<letterPosition, int> new_position) {
	position = new_position;
}


// Quenn 

Queen::Queen(string color, pair<letterPosition, int> pos)
	: ChessPiece(color, pos, 'Q') {}

bool Queen::canMoveTo(pair<letterPosition, int> target) {
	if ((target.first >= 1 && target.first <= 8) && (target.second >= 1 && target.second <= 8) && (target != position)) {
		bool horizontal = getPosition().first == target.first;
		bool vertical = getPosition().second == target.second;
		bool diagonal = abs(getPosition().second - target.second) == abs(getPosition().first - target.first);
		return horizontal || vertical || diagonal;
	}
	return false;
}

// Knight 

Knight :: Knight(string color, pair<letterPosition, int> pos):ChessPiece(color, pos, 'N') {}

bool Knight::canMoveTo(pair<letterPosition, int> target) {
	if ((target.first >= 1 && target.first <= 8) && (target.second >= 1 && target.second <= 8)) {
		int dx = abs(target.first - getPosition().first);
		int dy = abs(target.second - getPosition().second);
		return (dx == 1 && dy == 2) || (dx == 2 && dy == 1);
	}
	return false;
}



// Bishop 

Bishop :: Bishop(string color, pair<letterPosition, int> pos):ChessPiece(color, pos, 'B') {}

bool Bishop::canMoveTo(pair<letterPosition, int> target) {
	if ((target.first >= 1 && target.first <= 8) && (target.second >= 1 && target.second <= 8) && (target != position)) {
		return (abs(target.first - getPosition().first) == abs(target.second - getPosition().second));
	}
	return false;
}


// King 

King :: King(string color, pair<letterPosition, int> pos) :ChessPiece(color, pos, 'K') {}

bool King::canMoveTo(pair<letterPosition, int> target) {
	if ((target.first >= 1 && target.first <= 8) && (target.second >= 1 && target.second <= 8) && (target != position)) {
		int horisontal = abs(target.first - getPosition().first);
		int vertical = abs(target.second - getPosition().second);
		
		return horisontal <= 1 && vertical <= 1;
	}
	return false;
}


// Rook

Rook :: Rook(string color, pair<letterPosition, int> pos) :ChessPiece(color, pos, 'R') {}

bool Rook::canMoveTo(pair<letterPosition, int> target) {
	if ((target.first >= 1 && target.first <= 8) && (target.second >= 1 && target.second <= 8)) {
		bool vertical = (target.first == getPosition().first) && (target.second != getPosition().second);
		bool horizontal = (target.second == getPosition().second) && (target.first != getPosition().first);
		return vertical || horizontal;
	}
	return false;
}


// Pawn 

Pawn :: Pawn(string color, pair<letterPosition, int> pos) :ChessPiece(color, pos, 'P') {}

bool Pawn::canMoveTo(pair<letterPosition, int> target) {
	if ((target.first >= 1 && target.first <= 8) && (target.second >= 1 && target.second <= 8)) {
		int direction = (getColor() == "White") ? 1 : -1;

		return (target.first == position.first && target.second == position.second + direction);
	}
	return false;
}

bool Pawn::canAttack(pair<letterPosition, int> target) {
	if (target.first < A || target.first > H || target.second < 1 || target.second > 8)
		return false;

	int direction = (getColor() == "White") ? 1 : -1;
	return (abs(target.first - position.first) == 1 &&
		target.second == position.second + direction);
}
