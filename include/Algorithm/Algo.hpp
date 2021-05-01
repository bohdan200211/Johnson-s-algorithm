#include <../Graph/Graph.hpp>

template <class T>
using arr = std::vector<T>;
using WeightMatrix = arr<arr<int>>;

class GraphAlgo {
public:
    static bool BellmanFord(const Graph & G, const WeightMatrix & W, size_t source);
    static void Dijkstra   (const Graph & G, const WeightMatrix & W, size_t source);
private:
    static void _initialize_single_source(arr<std::pair<int, int>> & DistPredecessor, int source);
    static void _relax(arr<std::pair<int, int>> & DistPredecessor, const WeightMatrix & W, int u, int v);
};

void GraphAlgo::_initialize_single_source(arr<std::pair<int, int>> & DistPredecessor, int source) {
    for (auto & x : DistPredecessor) {
        x.first  = INT32_MAX;
        x.second = -1;
    }
    DistPredecessor[source].first = 0;
}

void GraphAlgo::_relax(arr<std::pair<int, int>> & DistPredecessor, const WeightMatrix & W, int u, int v) {
    if (DistPredecessor[v].first  > DistPredecessor[u].first + W[u][v]) {
        DistPredecessor[v].first  = DistPredecessor[u].first + W[u][v];
        DistPredecessor[v].second = u;
    }
}


bool GraphAlgo::BellmanFord(const Graph & G, const WeightMatrix & W, size_t source) {
    arr<std::pair<int, int>> DistPredecessor;

    const int n = G.GetVtxSize();

    _initialize_single_source(DistPredecessor, source);
    for (int i = 1; i < n; i++) {
        for (int r = 0; r < n; r++) {
            for (int c = 0; c < n; c++) {
                if (W[r][c] == 1) {
                    _relax(DistPredecessor, W, r, c);
                }
            }
        }
    }

    for (int r = 0; r < n; r++) {
        for (int c = 0; c < n; c++) {
            if (W[r][c] == 1 && DistPredecessor[c].first  > DistPredecessor[r].first + W[r][c]) {
                return false;
            }
        }
    }

    return true;
}

void GraphAlgo::Dijkstra(const Graph &G, const WeightMatrix &W, size_t source) {

}

