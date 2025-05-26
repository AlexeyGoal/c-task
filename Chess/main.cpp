
#include <ctime>
#include <iostream>
#include "Figures.h"
#include "ChessBoard.h"
using namespace std;


int main()

{
    std::clock_t start;
    double duration;

    start = std::clock();
    setlocale(LC_ALL, "RU");
    try {
        string input_file = "input.txt";
        string output_file = "output.txt";
        
        ifstream test_file(input_file);
        if (!test_file) {
            throw runtime_error("File " + input_file + " not found!");
        }
        test_file.close();

        ChessBoard board(input_file);
        
        if (board.findMateInOne(output_file))
            cout << "Mate in 1 move was found"<<endl;
        else
            cout << "Mate  in 1 move wasnt found"<<endl;
       
        
        if (board.findMateInTwo(output_file))
            cout << "Mate in 2 moves was found" << endl;
        else
            cout << "Mate  in 1 moves wasnt found" << endl;
        
        
        
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }


    duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;

    cout << "program execution time: " << duration << '\n';
    return 0;
}


