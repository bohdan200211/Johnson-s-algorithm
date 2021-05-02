#include <FibonacciHeap/FibHeap.hpp>

#include "../Graph/Graph.hpp"

template <class T>
using arr = std::vector<T>;
using WeightMatrix = arr<arr<int>>;

class GraphAlgo {
public:
    static bool BellmanFord (const Graph & G, arr<std::pair<int, int>> & DistPredecessor,
                             const WeightMatrix & W, size_t source);
    static void Dijkstra    (const Graph & G, arr<std::pair<int, int>> & DistPredecessor,
                             const WeightMatrix & W, size_t source);

    static arr<arr<int>> Johnson (Graph G, WeightMatrix W);
private:
    static void _initialize_single_source (arr<std::pair<int, int>> & DistPredecessor, int source);
    static void _relax (arr<std::pair<int, int>> & DistPredecessor, const WeightMatrix & W, int u, int v);
};

void GraphAlgo::_initialize_single_source (arr<std::pair<int, int>> & DistPredecessor, int source) {
    for (auto & x : DistPredecessor) {
        x.first  = INT32_MAX;
        x.second = -1;
    }
    DistPredecessor[source].first = 0;
}

void GraphAlgo::_relax (arr<std::pair<int, int>> & DistPredecessor, const WeightMatrix & W, int u, int v) {
    if (DistPredecessor[u].first != INT32_MAX
        && DistPredecessor[v].first  > DistPredecessor[u].first + W[u][v]) {

        DistPredecessor[v].first  = DistPredecessor[u].first + W[u][v];
        DistPredecessor[v].second = u;
    }
}


bool GraphAlgo::BellmanFord (const Graph & G, arr<std::pair<int, int>> & DistPredecessor,
                            const WeightMatrix & W, size_t source) {

    const int n = G.GetVtxSize();

    _initialize_single_source(DistPredecessor, source);
    for (int i = 1; i < n; i++) {

        for (int u = 0; u < n; u++) {
            for (int v = 0; v < n; v++) {
                if (G.m_Edges[u][v] == 1) {
                    _relax(DistPredecessor, W, u, v);
                }
            }
        }
    }

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (G.m_Edges[u][v] == 1 && DistPredecessor[v].first > DistPredecessor[u].first + W[u][v]) {
                return false;
            }
        }
    }

    return true;
}

void GraphAlgo::Dijkstra (const Graph & G, arr<std::pair<int, int>> & DistPredecessor,
                         const WeightMatrix & W, size_t source) {

    _initialize_single_source(DistPredecessor, source);

    FibHeap<int, int> Q;
    arr<FibNode<int, int>*> TableVrtx(G.GetVtxSize());

    arr<bool> S(G.GetVtxSize(), true);

    for (int i = 0; i < G.GetVtxSize(); i++) {
        TableVrtx[i] = new FibNode<int, int>(DistPredecessor[i].first, i);
        Q.Insert(TableVrtx[i]);
    }

    FibNode<int, int> * sVrtx;
    while (!Q.isEmpty()) {
        sVrtx = Q.ExtractMinimumNode();

        int u = sVrtx->GetData();
        S[u] = false;
        for (int v = 0; v < G.GetVtxSize(); v++) {
            if (G.m_Edges[u][v] == 1 && S[v]) {
                _relax(DistPredecessor, W, u, v);
                Q.DecreaseKey(TableVrtx[v], W[u][v]);
            }
        }
    }
}

arr<arr<int>> GraphAlgo::Johnson(Graph G, WeightMatrix W) {
    const int n = G.GetVtxSize();

    G.m_Edges.emplace_back(n, 1);
    W.emplace_back(n, 0);

    for (int i = 0; i < G.GetVtxSize(); ++i) {
        G.m_Edges[i].push_back(0);
        W[i].push_back(0);
    }



    arr<std::pair<int, int>> h(G.GetVtxSize(), {0, 0});

    if (!BellmanFord(G, h, W, n)) {
        throw std::runtime_error("Bellman-Fold algo finished with exit code 0");
    }

    for (int u = 0; u < n; u++) {
        for (int v = 0; v < n; v++) {
            if (G.m_Edges[u][v] == 1) {
                W[u][v] += h[u].first - h[v].first;
            }
        }
    }
    G.m_Edges.pop_back();

    arr<arr<int>> D(n, arr<int>(n));

    arr<std::pair<int, int>> DistPredecessor(G.GetVtxSize(), {0, 0});
    for (int u = 0; u < n; ++u) {
        Dijkstra(G, DistPredecessor, W, u);

        for (int v = 0; v < n; ++v) {
            D[u][v] = DistPredecessor[v].first + h[v].first - h[u].first;
        }
    }

    return D;
}



