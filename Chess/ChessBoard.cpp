#include "ChessBoard.h"
#include <set>

// ����������� �������� ��������� ������ � �����
ChessBoard::ChessBoard(string& path,string curTurn) {
	currentTurn = curTurn;
	ifstream file(path);
	if (!file.is_open()) {
		throw runtime_error("�� ������� ������� ����");
	}

	string line;
	while (getline(file, line)) {
		if (line.empty()) continue;

		// ��������� ����� �����
		if (line.find("White:") != string::npos) {
			int count = stoi(line.substr(6)); // ��������� ����� ����� "White:"
			for (int i = 0; i < count; ++i) {
				if (!getline(file, line)) break;
				if (line.empty()) continue;
				addPiece(line, true);
			}
		}
		// ��������� ������ �����
		else if (line.find("Black:") != string::npos) {
			int count = stoi(line.substr(6)); // ��������� ����� ����� "Black:"
			for (int i = 0; i < count; ++i) {
				if (!getline(file, line)) break;
				if (line.empty()) continue;
				addPiece(line, false);
			}
		}
	}
    
    int kingCount = 0;
    for (auto piece : figures) {
        if (piece->getSymbol() == 'K') {
            kingCount++;
        }
    }
    if (kingCount < 2)
        throw runtime_error("must be two kings of different colors");
}

// ����� ��� ���������� ������ � ������ �����
void ChessBoard::addPiece(string& str, bool isWhite) {
	if (str.length() < 3) return;

	string color = isWhite ? "White" : "Black";
	if (toupper(str[0]) == 'K') {
		int kingCount = 0;
		for (auto piece : figures) {
			if (piece->getColor() == color && piece->getSymbol() == 'K') {
				kingCount++;
			}
		}
		if (kingCount >= 1) {
			return; // �� ��������� ������, ���� �� ��� ����
		}
	}
	// ����������� ����������
	letterPosition posX = static_cast<letterPosition>(str[1] - 'A' + 1);
	int posY = stoi(str.substr(2));

	// �������� �� ��������� �������� �������
	if (posX < A || posX > H || posY < 1 || posY > 8) {
		return;
	}

	// �������� �� ��������� ������
	if (isPositionOccupied({ posX,posY })) {
		return;
	}


	// ������ ������
	switch (str[0]) {
	case 'Q': figures.push_back(new Queen(color, { posX,posY })); break;
	case 'N': figures.push_back(new Knight(color, { posX,posY })); break;
	case 'B': figures.push_back(new Bishop(color, { posX,posY })); break;
	case 'K': figures.push_back(new King(color, { posX,posY })); break;
	case 'R': figures.push_back(new Rook(color, { posX,posY })); break;
	case 'P': figures.push_back(new Pawn(color, { posX,posY })); break;
	default:
		return;
	}
}



ChessBoard :: ~ChessBoard() {
	for (auto piece : figures) delete piece;
	figures.clear();
}

// ����� ����������� ��������� ������
bool ChessBoard::isPositionOccupied(pair<letterPosition, int> pos) {
	for (auto& piece : figures) {
		if (piece->getPosition() == pos) {
			return true;
		}
	}
	return false;
}



// ����� ��� ������ ��������� �����
void ChessBoard::printBoard() {
	cout << "Chessboard:\n";
	cout << "-----------------\n";

	// ����� ����� �����
	cout << "White figures:\n";
	for (const auto& piece : figures) {
		if (piece->getColor() == "White") {
			char col = 'A' + piece->getPosition().first - 1;
			int row = piece->getPosition().second;
			cout << piece->getSymbol() << " " << col << row << endl;
		}
	}

	// ����� ������ �����
	cout << "\nBlack figures:\n";
	for (const auto& piece : figures) {
		if (piece->getColor() == "Black") {
			char col = 'A' + piece->getPosition().first - 1;
			int row = piece->getPosition().second;
			cout << piece->getSymbol() << " " << col << row << endl;
		}
	}

	cout << "-----------------\n";
}



// ����� ������������ ��� ������
bool ChessBoard::isCheck(string color) {
    // ������� ������
    pair<letterPosition, int> kingPos;
    bool kingFound = false;
    for (auto piece : figures) {
        if (piece->getColor() == color && piece->getSymbol() == 'K') {
            kingPos = piece->getPosition();
            kingFound = true;
            break;
        }
    }
    if (!kingFound) return false;

    string opponentColor = (color == "White") ? "Black" : "White";

    for (auto piece : figures) {
        if (piece->getColor() != opponentColor) continue;

        char symbol = piece->getSymbol();

        // ����� (��������� ������ canAttack)
        if (symbol == 'P') {
            Pawn* pawn = dynamic_cast<Pawn*>(piece);
            if (pawn && pawn->canAttack(kingPos)) {
                return true;
            }
            continue;
        }

        // ���� (��������� canMoveTo, ���� �� �����)
        if (symbol == 'N') {
            if (piece->canMoveTo(kingPos)) {
                return true;
            }
            continue;
        }

        // �����, �����, ����� (��������� ����)
        if (piece->canMoveTo(kingPos)) {
            if (isPathClear(piece, kingPos)) {
                return true;
            }
        }
    }
    return false;
}

// ����� ������������ ������ �� �����-���� �������
ChessPiece* ChessBoard::PieceByPosition(pair<letterPosition, int> position) {
    for (auto piece : figures) {
        if (piece->getPosition() == position) {
            return piece;
        }
    }
    return nullptr; // ������ �����
}

// ����� ������� ��������� �������� �� ���� ����� ������� � �������.
bool ChessBoard::isPathClear(ChessPiece* attacker, pair<letterPosition, int> kingPos) {
    auto attackerPos = attacker->getPosition();
    char symbol = attacker->getSymbol();

    // 1. ���� ������ ����� ��������� ���� (������������� ������)
    if (symbol == 'N') {
        return true;
    }

    // 2. ����� (��� ��������� canAttack, ���� �� �����������)
    if (symbol == 'P') {
        return true;
    }

    // 3. ����� � ����� (������ �����)
    if (symbol == 'R' || symbol == 'Q') {
        // �������������� �������� (��������� �����)
        if (attackerPos.second == kingPos.second) {
            int step = (kingPos.first > attackerPos.first) ? 1 : -1;
            for (letterPosition x = static_cast<letterPosition>(static_cast<int>(attackerPos.first) + step);
                x != kingPos.first;
                x = static_cast<letterPosition>(static_cast<int>(x) + step)) {
                if (PieceByPosition({ x, attackerPos.second }) != nullptr) {
                    return false;
                }
            }
        }
        // ������������ �������� (��������� �����)
        else if (attackerPos.first == kingPos.first) {
            int step = (kingPos.second > attackerPos.second) ? 1 : -1;
            for (int y = attackerPos.second + step; y != kingPos.second; y += step) {
                if (PieceByPosition({ attackerPos.first, y }) != nullptr) {
                    return false;
                }
            }
        }
    }

    // 4. ���� � ����� (���������)
    if (symbol == 'B' || symbol == 'Q') {
        int dx = static_cast<int>(kingPos.first) - static_cast<int>(attackerPos.first);
        int dy = kingPos.second - attackerPos.second;
        if (abs(dx) == abs(dy)) { // ���������, ��� ��� ���������
            int stepX = (dx > 0) ? 1 : -1;
            int stepY = (dy > 0) ? 1 : -1;
            letterPosition x = static_cast<letterPosition>(static_cast<int>(attackerPos.first) + stepX);
            int y = attackerPos.second + stepY;
            while (x != kingPos.first && y != kingPos.second) {
                if (PieceByPosition({ x, y })) {
                    return false;
                }
                x = static_cast<letterPosition>(static_cast<int>(x) + stepX);
                y += stepY;
            }
        }
    }

    return true; 
}

// ����� ����������� ����������� ������ ���� �� ��� ����
bool ChessBoard :: canEscapeKing(ChessPiece* piece) {
    auto moves = allPositions(piece);
    string oponentColor = (piece->getColor() == "Black") ? "White" : "Black";
    
    for (auto move : moves) {
        auto oldPos = piece->getPosition();
        piece->setPosition(move);
        if (!isCheck(piece->getColor())) {
            piece->setPosition(oldPos);
            return true;
        }
        piece->setPosition(oldPos);
    }
    return false;
}

// ���������� ��� ���������� ���� ������
vector<pair<letterPosition, int>> ChessBoard::allPositions(ChessPiece* piece) {
    vector<pair<letterPosition, int>> moves;
    pair<letterPosition, int> currentPos = piece->getPosition();

    ChessPiece* king = nullptr;
    for (auto p : figures) {
        if (p->getColor() == piece->getColor() && p->getSymbol() == 'K') {
            king = p;
            break;
        }
    }

    if (piece->getSymbol() == 'K') {
        for (int dx = -1; dx <= 1; ++dx) {
            for (int dy = -1; dy <= 1; ++dy) {
                if (dx == 0 && dy == 0) continue; // ���������� ������� �������

                int newX = currentPos.first + dx;
                int newY = currentPos.second + dy;

                // ��������� ������� �����
                if (newX < A || newX > H || newY < 1 || newY > 8) continue;

                pair<letterPosition, int> target = {
                    static_cast<letterPosition>(newX), newY
                };

                // ���������, �� ������ �� ������ ����� �������
                bool occupiedByAlly = false;
                for (auto p : figures) {
                    if (p->getPosition() == target && p->getColor() == piece->getColor()) {
                        occupiedByAlly = true;
                        break;
                    }
                }
                if (occupiedByAlly) continue;

                auto oldPos = piece->getPosition();
                ChessPiece* capturedPiece = PieceByPosition(target);
                bool wasCaptured = false;

                if (capturedPiece) {
                    auto it = find(figures.begin(), figures.end(), capturedPiece);
                    if (it != figures.end()) {
                        figures.erase(it);
                        wasCaptured = true;
                    }
                }
                piece->setPosition(target);

                // ���������, �� ��� ����� �� ������ ����� ����
                bool inCheck = isCheck(piece->getColor());
                if (!inCheck) {
                    moves.push_back(target);
                }

                // ���������� �� ��� ����
                piece->setPosition(oldPos);
                if (wasCaptured) {
                    figures.push_back(capturedPiece);
                }

            }
            
        }

     return moves;
    }

    if (piece->getSymbol() == 'P') {
        Pawn* pawn = dynamic_cast<Pawn*>(piece);
        
        string color = piece->getColor();
        pair<letterPosition, int> forward = {
            currentPos.first,
            currentPos.second + (color == "White" ? 1 : -1)
        };

        if (forward.second >= 1 && forward.second <= 8 && !PieceByPosition(forward)) {
            auto originalPos = piece->getPosition();
            ChessPiece* capturedPiece = PieceByPosition(forward);
            if (!capturedPiece) {
                piece->setPosition(forward);
                if (!isCheck(color)) {
                    moves.push_back(forward);
                    
                }
                piece->setPosition(originalPos);
            }

        }

        for (int dx : {-1, 1}) {
            pair<letterPosition, int> attackPos = {
                static_cast<letterPosition>(currentPos.first + dx),
                currentPos.second + (color == "White" ? 1 : -1)
            };

            if (attackPos.first >= A && attackPos.first <= H &&
                attackPos.second >= 1 && attackPos.second <= 8) {
                ChessPiece* targetPiece = PieceByPosition(attackPos);
                bool wasCapture = false;
                if (targetPiece && targetPiece->getColor() != color && pawn->canAttack(attackPos)) {
                    auto it = find(figures.begin(), figures.end(), targetPiece);
                    if (it != figures.end()) {
                        figures.erase(it);
                        wasCapture = true;
                    }
                    piece->setPosition(attackPos);

                    if (!isCheck(piece->getColor()))
                        moves.push_back(attackPos);

                    piece->setPosition(currentPos);
                    if (wasCapture)
                        figures.push_back(targetPiece);

                }
            }
        }
        return moves;
    }

    // ��� ������ ����� (�����, ����, �����, ����)
    vector<pair<int, int>> directions;

    // ����� � ����� - �����������/���������
    if (piece->getSymbol() == 'R' || piece->getSymbol() == 'Q') {
        directions.insert(directions.end(), {
            {1, 0}, {-1, 0}, {0, 1}, {0, -1}
            });
    }

    // ���� � ����� - ���������
    if (piece->getSymbol() == 'B' || piece->getSymbol() == 'Q') {
        directions.insert(directions.end(), {
            {1, 1}, {1, -1}, {-1, 1}, {-1, -1}
            });
    }

    // ���� - ������ ����
    if (piece->getSymbol() == 'N') {
        directions.insert(directions.end(), {
            {2, 1}, {2, -1}, {-2, 1}, {-2, -1},
            {1, 2}, {1, -2}, {-1, 2}, {-1, -2}
            });
    }

    // ��������� ������ �����������
    for (auto dir : directions) {
        int dx = dir.first;
        int dy = dir.second;

        // ��� ���� - ������ ���� ������ � ������ �����������
        if (piece->getSymbol() == 'N') {
            int newX = currentPos.first + dx;
            int newY = currentPos.second + dy;

            if (newX >= A && newX <= H && newY >= 1 && newY <= 8) {
                pair<letterPosition, int> target = {
                    static_cast<letterPosition>(newX), newY
                };

                // ���������, �� ������ �� ������ ����� �������
                bool occupiedByAlly = false;
                for (auto p : figures) {
                    if (p->getPosition() == target && p->getColor() == piece->getColor()) {
                        occupiedByAlly = true;
                        break;
                    }
                }
                if (occupiedByAlly) continue;

                // ���������, �� ������� �� ��� ������ ��� ���
                if (!moveExposesKing(piece, target, king)) {
                    moves.push_back(target);
                }
            }
            continue;
        }

        // ��� ������ ����� - ��������� ��� �����
        for (int step = 1; step <= 8; ++step) {
            int newX = currentPos.first + dx * step;
            int newY = currentPos.second + dy * step;

            if (newX < A || newX > H || newY < 1 || newY > 8) break;

            pair<letterPosition, int> target = {
                static_cast<letterPosition>(newX), newY
            };

            // ��������� ��������� ������
            ChessPiece* targetPiece = PieceByPosition(target);
            if (targetPiece) {
                // ���� �� ������ ���� ������ - ������ �� ����
                if (targetPiece->getColor() == piece->getColor()) break;

                // ���� ��������� ������ - ����� �����, �� ������ �� ����
                if (!moveExposesKing(piece, target, king)) {
                    moves.push_back(target);
                }
                break;
            }

            // ������ ������ - ���������, �� ������� �� ��� ������
            if (!moveExposesKing(piece, target, king)) {
                moves.push_back(target);
            }
        }
    }

    return moves;
}


// ��������� �� ��������� �� ������ ������ ������ ��� ��� ����� ����
bool ChessBoard::moveExposesKing(ChessPiece* piece, pair<letterPosition, int> target, ChessPiece* king) {
    if (!piece || !king) return true;

    // ��������� �������� ���������
    auto originalPos = piece->getPosition();
    ChessPiece* capturedPiece = PieceByPosition(target);
    bool wasCaptured = false;

    // ���������� ���
    if (capturedPiece && capturedPiece->getColor() != piece->getColor()) {
        auto it = find(figures.begin(), figures.end(), capturedPiece);
        if (it != figures.end()) {
            figures.erase(it);
            wasCaptured = true;
        }
    }
    piece->setPosition(target);

    // ���������, �� ��� ����� �� ������
    bool inCheck = isCheck(piece->getColor());

    // ���������� �� ��� ����
    piece->setPosition(originalPos);
    if (wasCaptured) {
        figures.push_back(capturedPiece);
    }

    return inCheck;
}

// ��������� ����� �� ������������� ��� ��� ������ ��������� ������(���� ������ ��� �����).
bool ChessBoard::BlockOrEat(ChessPiece* king) {
    // 1. ������� ��� ������, ������� ������ ��� ������
    vector<ChessPiece*> checkingPieces;
    for (auto piece : figures) {
        if (piece->getColor() != king->getColor()) {
            // ��� ����� ���������� ����������� �������� �����
            if (piece->getSymbol() == 'P') {
                Pawn* pawn = dynamic_cast<Pawn*>(piece);
                if (pawn && pawn->canAttack(king->getPosition())) {
                    checkingPieces.push_back(piece);
                }
            }
            // ��� ��������� ����� ����������� ��������
            else if (piece->canMoveTo(king->getPosition())) {
                checkingPieces.push_back(piece);
            }
        }
    }

    // ���� ��� ���� - ������ �� �����
    if (checkingPieces.empty()) return true;

    // ���� ��������� ����� ������ ��� - ������ ��� ������ ����� ������
    if (checkingPieces.size() > 1) return false;

    ChessPiece* attacker = checkingPieces[0];
    pair<letterPosition, int> attackerPos = attacker->getPosition();
    pair<letterPosition, int> kingPos = king->getPosition();

    

    
    for (auto defender : figures) {
        if (defender->getColor() == king->getColor() && defender->getSymbol() == 'P') {
            Pawn* pawn = dynamic_cast<Pawn*>(defender);
            if (pawn->canAttack(attackerPos)) {
                auto oldPos = defender->getPosition();
                defender->setPosition(attackerPos);

                auto it = find(figures.begin(), figures.end(), attacker);
                figures.erase(it);

                bool stillInCheck = isCheck(king->getColor());

                // ��������������� ���������
                figures.push_back(attacker);
                defender->setPosition(oldPos);

                if (!stillInCheck) {
                    return true;
                }
            }
        }

        if (defender->getColor() == king->getColor() &&
            defender != king &&
            defender->canMoveTo(attackerPos) && defender->getSymbol() != 'P') {

            // ��������� �� ��������� �� ��� ������ ��� ������ ����
            auto oldPos = defender->getPosition();
            defender->setPosition(attackerPos);

            // �������� ������� ��������� ������
            auto it = find(figures.begin(), figures.end(), attacker);
            figures.erase(it);

            bool stillInCheck = isCheck(king->getColor());

            // ��������������� ���������
            figures.push_back(attacker);
            defender->setPosition(oldPos);

            if (!stillInCheck) {
                return true;
            }
        }
    }

    // b) ������������� ����� ����� (��� �����, �����, �����)
    if (attacker->getSymbol() == 'Q' ||
        attacker->getSymbol() == 'R' ||
        attacker->getSymbol() == 'B') {

        // ��������� ����������� �����
        int dx = attackerPos.first - kingPos.first;
        int dy = attackerPos.second - kingPos.second;
        dx = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
        dy = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

        // ��������� ��� ������ ����� ������ � ��������� �������
        pair<letterPosition, int> blockPos = {
            static_cast<letterPosition>(kingPos.first + dx),
            kingPos.second + dy
        };

        while (blockPos != attackerPos) {
            // ��������� ����� �� ���� ������ ������ �� ����������� �������
            for (auto defender : figures) {
                if (defender->getColor() == king->getColor() &&
                    defender != king &&
                    defender->canMoveTo(blockPos)) {

                    // ��������� �� ��������� �� ��� ������
                    auto oldPos = defender->getPosition();
                    defender->setPosition(blockPos);

                    bool stillInCheck = isCheck(king->getColor());
                    defender->setPosition(oldPos);

                    if (!stillInCheck) {
                        return true;
                    }
                }
            }

            // ��������� � ��������� ������
            blockPos.first = static_cast<letterPosition>(blockPos.first + dx);
            blockPos.second += dy;
        }
    }


    return false;
}



// ����� ������� ���� ��� � 1 ���
bool ChessBoard::findMateInOne(string output_file) {
    
    ofstream outFile(output_file, ios::app);
    if (!outFile.is_open()) {
        cerr << "������: �� ������� ������� ���� ��� ������." << endl;
        return false;
    }

    outFile << "Mates in 1 move:" << endl;
    bool mateFound = false;
    string currentColor = currentTurn;
    string opponentColor = (currentColor == "White") ? "Black" : "White";

    // ������� ������ ����������
    ChessPiece* opponentKing = nullptr;
    for (auto piece : figures) {
        if (piece->getColor() == opponentColor && piece->getSymbol() == 'K') {
            opponentKing = piece;
            break;
        }
    }
    if (!opponentKing) return false;


    set<pair<letterPosition, int>> matePositions;
    for (auto piece : figures) {
        if (piece->getColor() != currentColor) continue;
        auto originalPos = piece->getPosition();
        auto moves = allPositions(piece); 
        for (auto move : moves) {
            // 1. ���������� ���
            
            ChessPiece* captured = PieceByPosition(move);
            bool wasCaptured = false;
            if (captured && captured->getColor() == opponentColor) {
                figures.erase(remove(figures.begin(), figures.end(), captured), figures.end());
                wasCaptured = true;
            }
            piece->setPosition(move);

            // 2. ��������� ��� � ���
            if (isCheck(opponentColor) &&
                allPositions(opponentKing).empty() &&
                !BlockOrEat(opponentKing)) {
                if (matePositions.insert(move).second){
                    char fromCol = 'A' + originalPos.first - 1;
                    int fromRow = originalPos.second;
                    char toCol = 'A' + move.first - 1;
                    int toRow = move.second;


                    outFile << piece->getSymbol() << fromCol << fromRow
                        << " -> " << piece->getSymbol() << toCol << toRow << endl;

                    mateFound = true;
                }
                
            }

            // 3. ���������� ���
            piece->setPosition(originalPos);
            if (wasCaptured) figures.push_back(captured);
        }
        
    }
    if (matePositions.size() == 0)
        outFile << "no mate found" << endl;

    return mateFound;
}

// ����� ������� ���� ��� � 2 ����
bool ChessBoard::findMateInTwo(string output_file) {
    ofstream outFile(output_file,ios::app);
    if (!outFile.is_open()) {
        cerr << "Error: Could not open output file." << endl;
        return false;
    }

    bool mateFound = false;
    string currentColor = currentTurn;
    string opponentColor = (currentColor == "White") ? "Black" : "White";

    // ��� �������� ���������� ������������������� �����
    set<string> uniqueSequences;

    
    

    // 1. ���������� ��� ��������� ������ ����
    for (auto p : figures) {
        
        if (p->getColor() != currentColor) continue;

        auto whiteOriginalPos = p->getPosition();
        auto whiteMoves = allPositions(p);

        for (auto whiteMove : whiteMoves) {
            // 1.1 ������ ������ ���
            ChessPiece* capturedFirst = PieceByPosition(whiteMove);
            bool firstCapture = false;
            if (capturedFirst && capturedFirst->getColor() == opponentColor) {
                auto it = find(figures.begin(), figures.end(), capturedFirst);
                if (it != figures.end()) {
                    figures.erase(it);
                    firstCapture = true;
                }
            }
            p->setPosition(whiteMove);

            // ���������� ���� ���� ������ ��� �����
            if (isCheck(currentColor)) {
                p->setPosition(whiteOriginalPos);
                if (firstCapture) figures.push_back(capturedFirst);
                continue;
            }

            // 2. ���������� ��� ��������� ������ ������
            for (auto blackP : figures) {
               
                if (blackP->getColor() != opponentColor) continue;

                auto blackOriginalPos = blackP->getPosition();
                auto blackMoves = allPositions(blackP);

                for (auto blackMove : blackMoves) {
                    // 2.1 ������ ��� ������
                    ChessPiece* capturedSecond = PieceByPosition(blackMove);
                    bool secondCapture = false;
                    if (capturedSecond && capturedSecond->getColor() == currentColor) {
                        auto it = find(figures.begin(), figures.end(), capturedSecond);
                        if (it != figures.end()) {
                            figures.erase(it);
                            secondCapture = true;
                        }
                    }
                    blackP->setPosition(blackMove);

                    // ���������� ���� ������ ������ ��� �����
                    if (isCheck(opponentColor)) {
                        blackP->setPosition(blackOriginalPos);
                        if (secondCapture) figures.push_back(capturedSecond);
                        continue;
                    }

                    // 3. ���������� ��� ��������� ������ ���� �����
                    for (size_t k = 0; k < figures.size(); ++k) {
                        auto matePiece = figures[k];
                        if (matePiece->getColor() != currentColor) continue;

                        auto mateOriginalPos = matePiece->getPosition();
                        auto mateMoves = allPositions(matePiece);

                        for (auto mateMove : mateMoves) {
                            // 3.1 ������ ������� ���
                            ChessPiece* capturedMate = PieceByPosition(mateMove);
                            bool mateCapture = false;
                            if (capturedMate && capturedMate->getColor() == opponentColor) {
                                auto it = find(figures.begin(), figures.end(), capturedMate);
                                if (it != figures.end()) {
                                    figures.erase(it);
                                    mateCapture = true;
                                }
                            }
                            matePiece->setPosition(mateMove);

                            // ��������� ���
                            if (!isCheck(currentColor) && isCheck(opponentColor)) {
                                ChessPiece* blackKing = nullptr;
                                for (auto p : figures) {
                                    if (p->getColor() == opponentColor && p->getSymbol() == 'K') {
                                        blackKing = p;
                                        break;
                                    }
                                }

                                if (blackKing) {
                                    auto kingMoves = allPositions(blackKing);
                                    

                                    if (kingMoves.empty() && !BlockOrEat(blackKing)) {
                                        // ��������� ��������� ������������� ������������������
                                        string sequence =
                                            "1. " + string(1, p->getSymbol()) +
                                            char(whiteOriginalPos.first + 'A' - 1) + to_string(whiteOriginalPos.second) +
                                            "->" +
                                            char(whiteMove.first + 'A' - 1) + to_string(whiteMove.second) + "\n" +
                                            "2. " + string(1, blackP->getSymbol()) +
                                            char(blackOriginalPos.first + 'A' - 1) + to_string(blackOriginalPos.second) +
                                            "->" +
                                            char(blackMove.first + 'A' - 1) + to_string(blackMove.second) + "\n" +
                                            "3. " + string(1, matePiece->getSymbol()) +
                                            char(mateOriginalPos.first + 'A' - 1) + to_string(mateOriginalPos.second) +
                                            "->" +
                                            char(mateMove.first + 'A' - 1) + to_string(mateMove.second);

                                        // ��������� ������������
                                        if (uniqueSequences.insert(sequence).second) {
                                            outFile << "Mate in 2 moves:\n" << sequence << "\n\n";
                                            mateFound = true;
                                        }
                                    }
                                }
                            }

                            // �������� ������� ���
                            matePiece->setPosition(mateOriginalPos);
                            if (mateCapture) figures.push_back(capturedMate);
                        }
                    }

                    // �������� ��� ������
                    blackP->setPosition(blackOriginalPos);
                    if (secondCapture) figures.push_back(capturedSecond);
                }
            }

            // �������� ������ ��� �����
            p->setPosition(whiteOriginalPos);
            if (firstCapture) figures.push_back(capturedFirst);
        }
    }

    if (uniqueSequences.size() == 0)
        outFile << "no mate was found" << endl;

    outFile.close();
    return mateFound;
}



