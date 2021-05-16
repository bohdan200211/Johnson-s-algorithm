//
// Created by Bohdan on 2021-05-01.
//

#pragma once

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

template <class T>
using arr = std::vector<T>;

class GraphAlgo;

class Graph {
private:
    using Type = int;

    arr<arr<Type>>    m_Edges;
    const std::string Path;

    friend class GraphAlgo;

public:
    explicit Graph(const std::string & path);

          Type & operator()(size_t idx, size_t idy)       { return m_Edges[idx][idy]; }
    const Type & operator()(size_t idx, size_t idy) const { return m_Edges[idx][idy]; }

    size_t GetVtxSize() const;
    const arr<arr<Type>> & GetEdges () const { return m_Edges; }
    void PrintGraph() const;
};

Graph::Graph(const std::string & _path)
    : Path(_path) {

    const std::string relativePath = "../../" + _path;

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

    while (getline(dotFile, text)) {
        if (text[0] == '}') {
            break;
        }

        std::istringstream iss(text);

        //read source vertex
        iss >> word;
        int SourceVertex = std::stoi(word);

        //skip "-> {"
        iss >> word;
        iss >> word;


        while (iss >> word && word[0] != '}') {
            int temp                    = std::stoi(word);
            m_Edges[SourceVertex][temp] = 1;
        }
    }

    dotFile.close();
}

void Graph::PrintGraph() const {
    std::string path = "dot -Tpdf ../../" + Path + " -o ../../" + Path.substr(0, Path.size() - 3) + "pdf";
    system(path.c_str());
}

size_t Graph::GetVtxSize() const { return m_Edges.size(); }
//"dot -Tpdf ../../src/graph.dot -o ../../src/outfile.pdf"
