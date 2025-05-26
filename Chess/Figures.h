#ifndef FIGURES_H
#define FIGURES_H
#include <string>
#include <cmath>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;


enum letterPosition{A = 1,B = 2,C = 3,D = 4,E = 5,F = 6, G = 7, H =8};

class ChessPiece {
protected:
	string Color;
	pair <letterPosition, int> position;
	char Symbol;
public:
	ChessPiece(string color, pair<letterPosition, int> pos, char symbol);
	string getColor();
	pair<letterPosition, int> getPosition();
	char getSymbol();
	void setPosition(pair<letterPosition, int> new_position);
	virtual bool canMoveTo(pair<letterPosition, int> target) = 0;
};


class Queen : public ChessPiece {
public: 
	Queen(string color, pair<letterPosition, int>);
	bool canMoveTo(pair<letterPosition, int> target) override;
};

class Knight : public ChessPiece {
public:
	Knight(string color, pair<letterPosition, int>);
	bool canMoveTo(pair<letterPosition, int> target) override;
};

class Bishop : public ChessPiece {
public:
	Bishop(string color, pair<letterPosition, int>);
	bool canMoveTo(pair<letterPosition, int> target) override;
};

class King : public ChessPiece {
public:
	King(string color, pair<letterPosition, int>);
	bool canMoveTo(pair<letterPosition, int> target) override;
	
};

class Rook : public ChessPiece {
public:
	Rook(string color, pair<letterPosition, int>);
	bool canMoveTo(pair<letterPosition, int> target) override;
};

class Pawn : public ChessPiece {
public:
	Pawn(string color,pair<letterPosition, int>);
	bool canMoveTo(pair<letterPosition, int> target) override;
	bool canAttack(pair<letterPosition, int> target);
};





#endif
