#include <iostream>

#include <Algo.hpp>
#include "fort.hpp"

void GenerateDot (const int n, const std::string & path, float probability = 0.5) {
    srand(time(nullptr));

    float prcProb = probability * 100;

    const std::string relativePath = "../../" + path;

    std::ofstream dotFile;
    dotFile.open(relativePath);

    dotFile << "# " + std::to_string(n) + "\n";
    dotFile << "digraph {\n";


    float pfd;
    for (int u = 0; u < n; ++u) {
        dotFile << std::to_string(u) << " -> { ";

        for (int v = 0; v < n; ++v) {
            pfd = rand() % 100;
            if (pfd < prcProb && v != u) {
                dotFile << std::to_string(v) << ' ';
            }
        }

        dotFile << "}\n";
    }


    dotFile << "}";

    dotFile.close();
}

arr<arr<int>> GenerateWeightedMatrix (const int n, const arr<arr<int>> & E, const int mod = 10) {
    srand(time(nullptr));
    arr<arr<int>> W(n, arr<int>(n, 0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (E[i][j]) {
                W[i][j] = rand() % mod/* - mod / 5*/;
//                W[i][j] = i + j;
            }
        }
    }

    return W;
}

void PrintMatrix (const arr<arr<int>> & Mtx) {
    const int n = Mtx.size();

    fort::char_table table;

    table << fort::header;

    table[0][0] = "u/v";
    table[0][0].set_cell_content_text_style(fort::text_style::bold);
    table[0][0].set_cell_content_fg_color(fort::color::cyan);
    for (int i = 1; i <= n; ++i) {
        table[0][i] = std::to_string(i - 1);
        table[i][0] = std::to_string(i - 1);

        table[0][i].set_cell_content_fg_color(fort::color::light_red);
        table[i][0].set_cell_content_fg_color(fort::color::light_red);

        table[0][i].set_cell_text_align(fort::text_align::center);
        table[i][0].set_cell_text_align(fort::text_align::center);
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (Mtx[i - 1][j - 1] != 0) table[i][j].set_cell_content_fg_color(fort::color::light_green);


            table[i][j] = std::to_string(Mtx[i - 1][j - 1]);
        }
    }

    std::cout << table.to_string() << std::endl;
}

int main () try {
    const char * dotPath = "src/G.dot";
    const int n          = 7;

    //?????????????????? ??????????
    GenerateDot(n, dotPath, 0.3);
    //?????????????????? ??????????
    Graph G(dotPath);
    auto & E = G.GetEdges();
    //?????????????????? ?????????????? ??????????????
    arr<arr<int>> W = std::move(GenerateWeightedMatrix(n, E));



    //????????????????
    arr<arr<int>> D = GraphAlgo::Johnson(G, W);


    //??????????
    G.PrintGraph();


    std::cout << "********************  W  ********************\n";
    PrintMatrix(W);

    std::cout << "********************  D  ********************\n";
    PrintMatrix(D);

} catch (const std::exception & ex) {
    std::cout << ex.what();
}