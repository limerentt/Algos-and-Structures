#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <limits>

using ll = long long;
const ll inf = std::numeric_limits<ll>::max();

void read_input(std::vector<std::vector<ll>>& neighbours,
                std::map<std::pair<ll, ll>, ll>& edge_cost, ll m) {
    ll v, u, cost;
    for (ll e = 0; e < m; ++e) {
        std::cin >> v >> u >> cost, --v, --u;
        neighbours[u].push_back(v);
        neighbours[v].push_back(u);
        edge_cost[{v, u}] = edge_cost[{u, v}] = cost;
    }
}

void find_shortest_dist(std::vector<std::vector<ll>>& neighbours,
                        std::map<std::pair<ll, ll>, ll>& edge_cost,
                        std::vector<ll>& dist,
                        ll start, ll n) {
    std::vector<bool> used(n, false);
    dist[start] = 0;

    std::set<std::pair<ll, ll>> weight;
    weight.insert({0, start});

    while (!weight.empty()) {
        ll vertex = (*weight.begin()).second;
        weight.erase(weight.begin());

        for (auto son: neighbours[vertex]) {
            if (dist[son] > dist[vertex] + edge_cost[{vertex, son}]) {
                dist[son] = dist[vertex] + edge_cost[{vertex, son}];
                weight.insert({dist[son], son});
            }
        }
    }
}

int main() {
    ll n, m;
    std::cin >> n >> m;

    ll start, finish;
    std::cin >> start >> finish, --start, --finish;

    std::vector<std::vector<ll>> neighbours(n);
    std::map<std::pair<ll, ll>, ll> edge_cost;
    read_input(neighbours, edge_cost, m);

    std::vector<ll> dist(n, inf);
    find_shortest_dist(neighbours, edge_cost, dist, start, n);

    std::cout << (dist[finish] == inf ? -1 : dist[finish]);
}
