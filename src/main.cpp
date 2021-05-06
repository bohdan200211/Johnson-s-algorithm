#include <iostream>

#include <Algo.hpp>



int main () try {
//

    Graph G("src/G.dot");

    arr<arr<int>> W = {
            {0, 3, 8, 0, -4},
            {0, 0, 0, 1, 7},
            {0, 4, 0, 0, 0},
            {2, 0, -5, 0, 0},
            {0, 0, 0, 6, 0}
    };

    arr<arr<int>> D = GraphAlgo::Johnson(G, W);


    G.PrintGraph();


    /*for (auto & row : D) {
        for (auto & cell : row) {
            std::cout << cell << ' ';
        }
        std::cout << std::endl;
    }*/

} catch (const std::exception & ex) {
    std::cout << ex.what();
}