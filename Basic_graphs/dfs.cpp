#include <iostream>
#include <vector>

using ll = long long;

class Graph {
private:
    std::vector<std::vector<ll>> neighbours;
public:
    explicit Graph (std::vector<std::vector<ll>>& neighbours): neighbours(neighbours) {}
    
    void dfs(ll v, std::vector<char>& color, std::vector<ll>& tin, std::vector<ll>& tout, ll& timer) {
        tin[v] = timer++;
        color[v] = 'g';
        for (auto son: neighbours[v]) {
            if (color[son] != 'w')
                continue;
            dfs(son, color, tin, tout, timer);
        }
        tout[v] = timer++;
        color[v] = 'b';
    }
};

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    ll V;
    std::cin >> V;

    std::vector<std::vector<ll>> neighbours(V);

    ll root, parent_input;
    for (size_t u = 0; u < V; ++u) {
        std::cin >> parent_input, --parent_input;
        if (parent_input != -1)
            neighbours[parent_input].push_back(u);
        else
            root = u;
    }

    Graph graph(neighbours);

    std::vector<char> color(V, 'w');
    std::vector<ll> parent(V, -1);
    std::vector<ll> tin(V);
    std::vector<ll> tout(V);
    ll timer = 0;
    graph.dfs(root, color, tin, tout, timer);

    ll number_of_tests;
    std::cin >> number_of_tests;
    ll v, u;
    while (number_of_tests--) {
        std::cin >> v >> u, --v, --u;
        std::cout << (tin[v] <= tin[u] && tout[v] >= tout[u]) << "\n";
    }
}
