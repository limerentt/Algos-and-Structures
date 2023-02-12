#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using ll = long long;

void read_input(ll n, ll m, std::unordered_map<ll, std::unordered_set<ll>>& neighbours) {
    ll vertex, son;
    for (ll i = 0; i < m; ++i) {
        std::cin >> vertex >> son, --vertex, --son;
        neighbours[vertex].insert(son + n);
    }
}

void dfs(ll v, std::unordered_map<ll, std::unordered_set<ll>>& neighbours, std::unordered_map<ll, bool>& used) {
    used[v] = true;
    for (auto son: neighbours[v]) {
        if (used[son]) continue;
        dfs(son, neighbours, used);
    }
}

bool augment(ll v, std::unordered_map<ll, bool>& used,
             std::unordered_map<ll, std::unordered_set<ll>>& neighbours,
             std::unordered_map<ll, ll>& match,
             std::unordered_map<ll, ll>& reverse_match) {
    if (used[v]) return false;
    used[v] = true;
    for (ll son: neighbours[v]) {
        if (!match.contains(son) || augment(match[son], used, neighbours, match, reverse_match)) {
            match[son] = v, reverse_match[v] = son;
            return true;
        }
    }
    return false;
}

ll find_num_of_paths(ll n, std::unordered_map<ll, std::unordered_set<ll>>& neighbours) {
    std::unordered_map<ll, ll> match, reverse_match;
    std::unordered_map<ll, bool> used;

    for (const auto& v: neighbours) {
        if (augment(v.first, used, neighbours, match, reverse_match)) used.clear();
    }

    neighbours.clear();
    for (const auto& u: match) {
        neighbours[u.first].insert(u.second);
        neighbours[u.second].insert(u.first);
    }

    for (ll i = 0; i < n; ++i) {
        neighbours[i].insert(i + n);
        neighbours[i + n].insert(i);
    }

    used.clear();
    ll num_of_paths = 0;
    for (ll v = 0; v < n; ++v) {
        if (!used.contains(v)) {
            dfs(v, neighbours, used);
            ++num_of_paths;
        }
    }
    return num_of_paths;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll n, m;
    std::cin >> n >> m;

    std::unordered_map<ll, std::unordered_set<ll>> neighbours;
    read_input(n, m, neighbours);

    std::cout << find_num_of_paths(n, neighbours);
}
