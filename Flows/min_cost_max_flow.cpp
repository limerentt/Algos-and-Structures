#include <bits/stdc++.h>

using namespace std;
using ll = long long;
const ll inf = numeric_limits<ll>::max();

ll n;

void dijkstra(unordered_map<ll, unordered_set<ll>>& nei,
          map<vector<ll>, pair<ll, ll>>& cost_capacity,
          ll s, vector<pair<ll, ll>>& parent, vector<ll>& dist) {
    vector<bool> busy(n, false);
    queue<ll> q;
    parent.assign(n, {-1, 0}), dist.assign(n, inf);

    dist[s] = 0;
    q.push(s);

    while (!q.empty()) {
        ll v = q.front();
        q.pop();
        busy[v] = false;

        for (ll u: nei[v]) {
            ll j = 0;
            while (cost_capacity.contains({v, u, j})) {
                if (cost_capacity[{v, u, j}].second > 0 &&
                    dist[u] > dist[v] + cost_capacity[{v, u, j}].first) {
                    dist[u] = dist[v] + cost_capacity[{v, u, j}].first;
                    parent[u] = {v, j};
                    if (!busy[u]) {
                        q.push(u);
                        busy[u] = true;
                    }
                }
                ++j;
            }
        }
    }
}

uint64_t MCMF(unordered_map<ll, unordered_set<ll>>& nei,
        map<vector<ll>, pair<ll, ll>>& cost_capacity,
        ll s, ll t) {
    uint64_t cost = 0;
    vector<ll> dist;
    vector<pair<ll, ll>> parent;
    while (true) {
        dijkstra(nei, cost_capacity, s, parent, dist);
        if (dist[t] == inf) break;

        ll delta = inf;

        for (ll v = t; v != s; v = parent[v].first) {
            delta = min(delta, cost_capacity[{parent[v].first, v, parent[v].second}].second);
        }

        for (ll v = t; v != s; v = parent[v].first) {
            cost += delta * cost_capacity[{parent[v].first, v, parent[v].second}].first;
            cost_capacity[{parent[v].first, v, parent[v].second}].second -= delta;
            cost_capacity[{v, parent[v].first, parent[v].second}].second += delta;
        }
    }
    return cost;
}

signed main() {
    ll m;
    cin >> n >> m;

    ll s = 0, t = n - 1;

    unordered_map<ll, unordered_set<ll>> nei;
    map<vector<ll>, pair<ll, ll>> cost_capacity;

    ll read_parent, read_son, read_capacity, read_cost;
    for (ll i = 0; i < m; ++i) {
        cin >> read_parent >> read_son >> read_capacity >> read_cost, --read_parent, --read_son;
        ll j = 0;
        while (cost_capacity.contains({read_parent, read_son, j})) ++j;
        nei[read_parent].insert(read_son);
        cost_capacity[{read_parent, read_son, j}] = {read_cost, read_capacity};
        nei[read_son].insert(read_parent);
        cost_capacity[{read_son, read_parent, j}] = {-read_cost, 0};
    }

    cout << MCMF(nei, cost_capacity, s, t);
}
