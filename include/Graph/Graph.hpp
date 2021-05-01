//
// Created by Bohdan on 2021-05-01.
//

#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

class Graph {
private:
    using Type = int;

    std::vector<std::vector<Type>> m_Edges;
    const std::string              relativePath;

public:
    explicit Graph(const std::string & path);

          Type & operator()(size_t idx, size_t idy)       { return m_Edges[idx][idy]; }
    const Type & operator()(size_t idx, size_t idy) const { return m_Edges[idx][idy]; }

    size_t GetVtxSize() const;
    void PrintGraph() const;
};

Graph::Graph(const std::string & path)
    : relativePath("../../" + path) {

    std::ifstream dotFile;
    dotFile.open(relativePath);
    if (!dotFile) {
        throw std::runtime_error("Unable to open file .dot");
    }



    std::string text;

    //read amount of vertices
    getline(dotFile, text);

    int Size = std::stoi(text.substr(1, text.size()));
    m_Edges.resize(Size, std::vector<Type>(Size, 0));



    //skip line
    getline(dotFile, text);

    //read input
    std::string word;
    int prev_v_id;

    while (getline(dotFile, text)) {
        if (text[0] == '}') {
            break;
        }

        prev_v_id = -1;

        std::istringstream iss(text);
        while (iss >> word) {
            if (prev_v_id == -1) {
                prev_v_id = std::stoi(word);
            }
            else if (word != "->") {
                int temp                 = std::stoi(word);
                m_Edges[prev_v_id][temp] = 1;
                prev_v_id                = temp;
            }
        }
    }

    dotFile.close();
}

void Graph::PrintGraph() const {
    std::string Path = "dot -Tpdf " + relativePath + " -o ../../src/outfile.pdf";
    system(Path.c_str());
}

size_t Graph::GetVtxSize() const { return m_Edges.size(); }
//"dot -Tpdf ../../src/graph.dot -o ../../src/outfile.pdf"
