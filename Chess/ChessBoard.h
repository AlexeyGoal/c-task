#ifndef BOARD_H
#define BOARD_H

#include "Figures.h"


class ChessBoard {
private:
	
	string currentTurn;
	vector<ChessPiece*> figures;

	bool moveExposesKing(ChessPiece* piece, pair<letterPosition, int> target, ChessPiece* king);
	ChessPiece* PieceByPosition(pair<letterPosition, int> position);
	bool isPathClear(ChessPiece* attacker, pair<letterPosition, int> kingPos);
	bool canEscapeKing(ChessPiece* piece);
	bool BlockOrEat(ChessPiece* piece);
	vector<pair<letterPosition, int >> allPositions(ChessPiece* piece);
	void addPiece(string& str, bool isWhite);
	bool isPositionOccupied(pair<letterPosition, int> pos);
	bool isCheck(string color);
	
public:
	
	bool findMateInTwo(string output_file);
	ChessBoard(string& path,string curTurn = "White");
	~ChessBoard();
	void printBoard();
	bool findMateInOne(string output_file);
	
};


#endif
