#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>

using ll = long long;

void read_input(ll m, std::unordered_map<ll, std::unordered_multiset<ll>>& neighbours) {
    ll read_parent, read_son;
    for (ll i = 0; i < m; ++i) {
        std::cin >> read_parent >> read_son, --read_parent, --read_son;
        neighbours[read_parent].insert(read_son);
    }
}

bool bfs(ll n, std::unordered_map<ll, std::unordered_multiset<ll>>& neighbours, ll s, ll t, std::vector<ll>& parent) {
    std::vector<bool> visited(n, false);
    std::queue<ll> q;
    parent.assign(n, -1);

    q.push(s);
    visited[s] = true;

    while (!q.empty()) {
        ll u = q.front();
        q.pop();

        for (ll v: neighbours[u]) {
            if (visited[v]) continue;
            parent[v] = u;
            if (v == t) return true;
            q.push(v);
            visited[v] = true;
        }
    }
    return false;
}

ll ford_fulkerson(ll n, std::unordered_map<ll, std::unordered_multiset<ll>>& neighbours,
                  std::unordered_map<ll, std::unordered_multiset<ll>>& paths_neighbours,
                  ll s, ll t, std::vector<ll>& parent, std::vector<std::pair<ll, ll>>& edges_to_delete) {
    std::multiset<std::pair<ll, ll>> negative_edges;
    ll max_flow = 0;
    while (bfs(n, neighbours, s, t, parent) && max_flow < 2) {
        for (ll v = t; v != s; v = parent[v]) {
            if (negative_edges.contains({parent[v], v})) {
                edges_to_delete.push_back({parent[v], v});
                edges_to_delete.push_back({v, parent[v]});
            }
            paths_neighbours[parent[v]].insert(v);
            neighbours[parent[v]].erase(neighbours[parent[v]].find(v));
            neighbours[v].insert(parent[v]);
            negative_edges.insert({v, parent[v]});
        }
        ++max_flow;
    }
    return max_flow;
}

bool two_paths_exist(ll n, std::unordered_map<ll, std::unordered_multiset<ll>>& neighbours,
                     std::unordered_map<ll, std::unordered_multiset<ll>>& paths_neighbours,
                     ll s, ll t, std::vector<ll>& parent, std::vector<std::pair<ll, ll>>& edges_to_delete) {
    if (ford_fulkerson(n, neighbours, paths_neighbours, s, t, parent, edges_to_delete) < 2) {
        std::cout << "NO";
        return false;
    } else {
        std::cout << "YES" << '\n';
        return true;
    }
}

void print_both_paths(ll s, ll t, std::unordered_map<ll, std::unordered_multiset<ll>>& paths_neighbours,
                      std::vector<std::pair<ll, ll>>& edges_to_delete) {
    std::map<std::pair<ll, ll>, bool> deleted_edges;

    for (auto e: edges_to_delete) {
        paths_neighbours[e.first].erase(paths_neighbours[e.first].find(e.second));
    }

    ll current_parent;
    deleted_edges.clear();
    edges_to_delete.clear();
    for (ll v = s; v != t; v = *paths_neighbours[v].begin()) {
        std::cout << v + 1 << ' ';
        if (v != s && !deleted_edges.contains({current_parent, v})) {
            edges_to_delete.push_back({current_parent, v});
            deleted_edges[{current_parent, v}] = true;
        }
        current_parent = v;
    }
    if (!deleted_edges.contains({current_parent, t})) edges_to_delete.push_back({current_parent, t});
    std::cout << t + 1 << '\n';

    for (auto e: edges_to_delete) {
        paths_neighbours[e.first].erase(paths_neighbours[e.first].find(e.second));
    }

    for (ll v = s; v != t; v = *paths_neighbours[v].begin()) {
        std::cout << v + 1 << ' ';
    }
    std::cout << t + 1;
}

int main() {
    ll n, m, s, t;
    std::cin >> n >> m >> s >> t, --s, --t;

    std::unordered_map<ll, std::unordered_multiset<ll>> neighbours, paths_neighbours;
    read_input(m, neighbours);

    std::vector<ll> parent(n, -1);
    std::vector<std::pair<ll, ll>> edges_to_delete;
    
    if (!two_paths_exist(n, neighbours, paths_neighbours, s, t, parent, edges_to_delete)) return 0;
    print_both_paths(s, t, paths_neighbours, edges_to_delete);
}
