#include <iostream>
#include <vector>
#include <set>

using ll = long long;

class Graph {
private:
    std::vector<std::set<ll>> edges;
public:
    explicit Graph (std::vector<std::set<ll>> edges): edges(edges) {}

    void find_euler_cycle(ll v, std::vector<ll>& vertices_of_cycle) {
        while (!edges[v].empty()) {
            ll u = *edges[v].begin();
            edges[v].erase(u);
            find_euler_cycle(u, vertices_of_cycle);
        }
        vertices_of_cycle.push_back(v);
    }  
};

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll V, A;
    std::cin >> V >> A, --A;
    char read;
    std::vector<std::set<ll>> edges(V);

    for (size_t i = 0; i < V; ++i) {
        for (size_t j = 0; j < V; ++j) {
            std::cin >> read;
            if (i == j)
                continue;
            if (read == '0')
                edges[i].insert(j);
        }
    }
    
    Graph graph(edges);

    std::vector<ll> vertices_of_cycle;
    graph.find_euler_cycle(A, vertices_of_cycle);

    for (size_t v = vertices_of_cycle.size() - 1; v >= 1; --v)
        std::cout << vertices_of_cycle[v] + 1 << " " << vertices_of_cycle[v - 1] + 1 << "\n";
}
