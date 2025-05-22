#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int ROWS = 6;
const int COLS = 7;
const char EMPTY = '.';
const char PLAYER1 = 'X';
const char PLAYER2 = 'O';

class ConnectFour {
private:
    vector<vector<char>> board;
    char currentPlayer;

public:
    ConnectFour() : board(ROWS, vector<char>(COLS, EMPTY)), currentPlayer(PLAYER1) {}

    void printBoard() {
        cout << "\n 1 2 3 4 5 6 7\n";
        for (const auto& row : board) {
            cout << "|";
            for (char cell : row) {
                cout << cell << "|";
            }
            cout << "\n";
        }
        cout << "---------------\n";
    }

    bool makeMove(int col) {
        col--; // Переводим в 0-based индекс
        if (col < 0 || col >= COLS || board[0][col] != EMPTY) {
            return false;
        }

        // Находим первую свободную ячейку в столбце
        for (int row = ROWS - 1; row >= 0; row--) {
            if (board[row][col] == EMPTY) {
                board[row][col] = currentPlayer;
                return true;
            }
        }
        return false;
    }

    bool checkWin() {
        // Проверка по горизонтали
        for (int row = 0; row < ROWS; row++) {
            for (int col = 0; col < COLS - 3; col++) {
                if (board[row][col] != EMPTY &&
                    board[row][col] == board[row][col + 1] &&
                    board[row][col] == board[row][col + 2] &&
                    board[row][col] == board[row][col + 3]) {
                    return true;
                }
            }
        }

        // Проверка по вертикали
        for (int row = 0; row < ROWS - 3; row++) {
            for (int col = 0; col < COLS; col++) {
                if (board[row][col] != EMPTY &&
                    board[row][col] == board[row + 1][col] &&
                    board[row][col] == board[row + 2][col] &&
                    board[row][col] == board[row + 3][col]) {
                    return true;
                }
            }
        }

        // Проверка по диагонали (слева направо вниз)
        for (int row = 0; row < ROWS - 3; row++) {
            for (int col = 0; col < COLS - 3; col++) {
                if (board[row][col] != EMPTY &&
                    board[row][col] == board[row + 1][col + 1] &&
                    board[row][col] == board[row + 2][col + 2] &&
                    board[row][col] == board[row + 3][col + 3]) {
                    return true;
                }
            }
        }

        // Проверка по диагонали (справа налево вниз)
        for (int row = 0; row < ROWS - 3; row++) {
            for (int col = 3; col < COLS; col++) {
                if (board[row][col] != EMPTY &&
                    board[row][col] == board[row + 1][col - 1] &&
                    board[row][col] == board[row + 2][col - 2] &&
                    board[row][col] == board[row + 3][col - 3]) {
                    return true;
                }
            }
        }

        return false;
    }

    bool isBoardFull() {
        for (int col = 0; col < COLS; col++) {
            if (board[0][col] == EMPTY) {
                return false;
            }
        }
        return true;
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == PLAYER1) ? PLAYER2 : PLAYER1;
    }

    char getCurrentPlayer() const {
        return currentPlayer;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    ConnectFour game;
    int move;
    bool gameOver = false;

   
    

    while (!gameOver) {
        game.printBoard();
        cout << "Ход игрока " << game.getCurrentPlayer() << ". Введите столбец (1-7): ";

        if (!(cin >> move)) {
            cout << "Некорректный ввод. Пожалуйста, введите число от 1 до 7.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (move < 1 || move > 7) {
            cout << "Столбец должен быть от 1 до 7. Попробуйте снова.\n";
            continue;
        }

        if (!game.makeMove(move)) {
            cout << "Этот столбец уже заполнен. Выберите другой.\n";
            continue;
        }

        if (game.checkWin()) {
            game.printBoard();
            cout << "Игрок " << game.getCurrentPlayer() << " победил! Поздравляем!\n";
            gameOver = true;
        }
        else if (game.isBoardFull()) {
            game.printBoard();
            cout << "Ничья! Игровое поле заполнено.\n";
            gameOver = true;
        }
        else {
            game.switchPlayer();
        }
    }

    return 0;
}
