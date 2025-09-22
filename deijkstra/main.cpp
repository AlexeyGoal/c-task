
#include <iostream>
#include"Graph.h"
#include <chrono>
#include <stdexcept>
int main()
{   
    try {
        auto start_time = chrono::high_resolution_clock::now();
        string file_path = "1000.txt";

        Graph g1(file_path);


        vector<string> path = g1.dijkstraShortestPath("0", "709");
        int distance = g1.dijkstraShortestDistance("0", "709");

        auto end_time = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time);

        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Total distance: " << distance << endl;
        cout << "Time taken: " << duration.count() << " ms" << endl;
    }
    catch (const exception& e) {
        cout << e.what();
    }

    return 0;
}


