#include <iostream>
#include <vector>
#include <set>

using ll = long long;

struct DisjointSet {
    std::vector<ll> parent;
    std::vector<ll> size;

    DisjointSet(ll maxSize) {
        parent.resize(maxSize);
        size.resize(maxSize);
        for (ll i = 0; i < maxSize; ++i) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    ll find_set(ll v) {
        if (v == parent[v]) return v;
        return parent[v] = find_set(parent[v]);
    }

    void union_set(ll a, ll b) {
        a = find_set(a), b = find_set(b);
        if (a != b) {
            if (size[a] < size[b]) std::swap(a, b);
            parent[b] = a;
            size[a] += size[b];
        }
    }
};

void read_input(ll m, std::vector<std::pair<ll, std::pair<ll, ll>>>& edges) {
    ll a, b, w;
    for (ll i = 0; i < m; ++i) {
        std::cin >> a >> b >> w, --a, --b;
        edges.push_back({w, {a, b}});
    }
    sort(edges.begin(), edges.end());
}

ll find_min_spanning_tree_weight(ll n, std::vector<std::pair<ll, std::pair<ll, ll>>>& edges) {
    ll weight = 0;
    DisjointSet ds(n);
    for (auto e: edges) {
        ll v = e.second.first, u = e.second.second;
        ll v_set = ds.find_set(v), u_set = ds.find_set(u);
        if (v_set != u_set) {
            weight += e.first;
            ds.union_set(v_set, u_set);
        }
    }
    return weight;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll n, m;
    std::cin >> n >> m;

    std::vector<std::pair<ll, std::pair<ll, ll>>> edges;
    read_input(m, edges);

    std::cout << find_min_spanning_tree_weight(n, edges);
}
