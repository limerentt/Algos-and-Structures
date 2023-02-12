#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits>

using ll = long long;
static const ll inf = std::numeric_limits<ll>::max();

void read_input(ll m, std::map<std::pair<ll, ll>, ll>& edges) {
    ll a, b, w;
    for (ll i = 0; i < m; ++i) {
        std::cin >> a >> b >> w, --a, --b;
        edges[{a, b}] = edges[{b, a}] = w;
    }
}

ll find_min_spanning_tree_weight(ll n, std::map<std::pair<ll, ll>, ll>& edges) {
    std::set<ll> not_visited;
    for (ll i = 0; i < n; ++i) {
        not_visited.insert(i);
    }

    std::vector<ll> parents(n, -1), dist(n, inf);
    dist[0] = 0, parents[0] = -1;

    ll weight = 0;
    while (!not_visited.empty()) {
        ll min_vertex, min_vertex_dist = inf;
        for (ll v: not_visited) {
            if (dist[v] < min_vertex_dist) {
                min_vertex_dist = dist[v];
                min_vertex = v;
            }
        }
        not_visited.erase(min_vertex);
        weight += edges[{min_vertex, parents[min_vertex]}];
        for (ll u: not_visited) {
            if (edges.contains({min_vertex, u}) && edges[{min_vertex, u}] < dist[u]) {
                parents[u] = min_vertex;
                dist[u] = edges[{min_vertex, u}];
            }
        }
    }
    return weight;
}

int main() {
    ll n, m;
    std::cin >> n >> m;
    std::map<std::pair<ll, ll>, ll> edges;
    read_input(m, edges);
    
    std::cout << find_min_spanning_tree_weight(n, edges);
}
