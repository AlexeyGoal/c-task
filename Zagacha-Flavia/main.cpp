#include "List.h"
#include <iostream>
#include <ctime>
#include <locale>

int findLastOne(int count, int step_size) {
    DynamicArray circle(count);

    
    for (int i = 1; i <= count; ++i) {
        circle.append(i);
    }

    int current_position = 0;

    
    while (circle.size() > 1) {
        current_position = (current_position + step_size - 1) % circle.size();
        circle.removeAt(current_position);
    }

    return circle[0];
}

int main() {
    setlocale(LC_ALL, "ru");

    int n, k;
    std::cout << "Введите количество элементов и размер шага: ";
    std::cin >> n >> k;

    clock_t start_time = clock();
    int survivor = findLastOne(n, k);
    clock_t end_time = clock();

    double elapsed_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    std::cout << "Ответ: " << survivor << std::endl;
    std::cout << "Время выполнения: " << elapsed_time << " секунд" << std::endl;

    return 0;
}


