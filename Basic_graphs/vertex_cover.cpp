#include <bits/stdc++.h>
using namespace std;
using ll = long long;

void dfs(ll v, const vector<set<ll>>& nei, vector<bool>& used) {
    used[v] = true;
    for (ll son: nei[v]) {
        if (used[son]) continue;
        dfs(son, nei, used);
    }
}

int main() {
    ll m, n;
    cin >> m >> n;

    vector<set<ll>> nei(m + n);
    ll k, neighbour;
    for (ll i = 0; i < m; ++i) {
        cin >> k;
        for (ll j = 0; j < k; ++j) {
            cin >> neighbour, --neighbour;
            nei[i].insert(m + neighbour);
            nei[m + neighbour].insert(i);
        }
    }

    vector<bool> in_match(m, false);
    for (ll i = 0; i < m; ++i) {
        cin >> neighbour, --neighbour;
        if (neighbour != -1) {
            nei[i].erase(m + neighbour);
            in_match[i] = true;
        }
    }

    vector<pair<ll, ll>> to_delete;
    for (ll i = m; i < n + m; ++i) {
        for (ll v: nei[i]) {
            if (nei[v].contains(i)) to_delete.push_back({i, v});
        }
    }

    for (pair<ll, ll> p: to_delete) {
        nei[p.first].erase(p.second);
    }

    vector<bool> used(m + n, false);
    for (ll v = 0; v < m; ++v) {
        if (!in_match[v] && !used[v]) dfs(v, nei, used);
    }

    vector<ll> coverage;
    ll size_first = 0, size_second = 0;
    for (ll v = 0; v < m; ++v) {
        if (!used[v]) {
            coverage.push_back(v);
            ++size_first;
        }
    }

    for (ll v = m; v < m + n; ++v) {
        if (used[v]) {
            coverage.push_back(v - m);
            ++size_second;
        }
    }

    cout << size_first + size_second << '\n';
    cout << size_first << ' ';
    for (ll v = 0; v < size_first; ++v) {
        cout << coverage[v] + 1 << ' ';
    }

    cout << '\n' << size_second << ' ';
    for (ll v = size_first; v < size_first + size_second; ++v) {
        cout << coverage[v] + 1 << ' ';
    }
}
