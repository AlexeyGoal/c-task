#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

// Генерация случайного 4-значного числа без повторяющихся цифр
string generateSecretNumber() {
    vector<int> digits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    random_shuffle(digits.begin(), digits.end());

    // Первая цифра не может быть 0
    if (digits[0] == 0) {
        swap(digits[0], digits[1]);
    }

    string secret;
    for (int i = 0; i < 4; ++i) {
        secret += to_string(digits[i]);
    }
    return secret;
}

// Проверка ввода пользователя
bool isValidGuess(const string& guess) {
    if (guess.length() != 4) return false;

    // Проверка, что все символы - цифры
    for (char c : guess) {
        if (!isdigit(c)) return false;
    }

    // Проверка на повторяющиеся цифры
    for (int i = 0; i < 4; ++i) {
        for (int j = i + 1; j < 4; ++j) {
            if (guess[i] == guess[j]) return false;
        }
    }

    return true;
}

// Подсчет быков и коров
pair<int, int> countBullsAndCows(const string& secret, const string& guess) {
    int bulls = 0;
    int cows = 0;

    for (int i = 0; i < 4; ++i) {
        if (secret[i] == guess[i]) {
            bulls++;
        }
        else if (secret.find(guess[i]) != string::npos) {
            cows++;
        }
    }

    return make_pair(bulls, cows);
}

int main() {
    setlocale(LC_ALL, "ru");
    srand(time(0)); // Инициализация генератора случайных чисел

    string secret = generateSecretNumber();
    int attempts = 0;
    string guess;

    
    cout << "Компьютер загадал 4-значное число без повторяющихся цифр.\n";
    cout << "Попробуйте угадать его!\n\n";

    while (true) {
        cout << "Введите вашу догадку (4 цифры без повторений): ";
        cin >> guess;

        if (!isValidGuess(guess)) {
            cout << "Некорректный ввод. Пожалуйста, введите 4-значное число без повторяющихся цифр.\n";
            continue;
        }

        attempts++;
        auto result = countBullsAndCows(secret, guess);

        cout << "Быки: " << result.first << ", Коровы: " << result.second << "\n";

        if (result.first == 4) {
            cout << "\nПоздравляем! Вы угадали число " << secret << " за " << attempts << " попыток!\n";
            break;
        }
    }

    return 0;
}
