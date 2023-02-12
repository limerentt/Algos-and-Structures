#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct node {
    ll len = 0;
    ll link = -1;
    ll num_of_paths = 1;
    bool visited = false;
    unordered_map<ll, ll> to;
};

void dfs(vector<node>& aut, ll v) {
    if (aut[v].visited) return;
    aut[v].visited = true;
    for (char c = 'a'; c <= 'z'; ++c) {
        if (aut[v].to.contains(c - 'a')) {
            dfs(aut, aut[v].to[c - 'a']);
            aut[v].num_of_paths += aut[aut[v].to[c - 'a']].num_of_paths;
        }
    }
}

void enhance_aut(vector<node>& aut, char c, ll& last) {
    ll cur_v = aut.size();
    aut.push_back(node());
    aut[cur_v].len = aut[last].len + 1;
    ll p = last;
    while (p != -1 && !aut[p].to.contains(c - 'a')) {
        aut[p].to[c - 'a'] = cur_v;
        p = aut[p].link;
    }
    if (p == -1) {
        aut[cur_v].link = 0;
        last = cur_v;
        return;
    }
    ll q = aut[p].to[c - 'a'];
    if (aut[q].len == aut[p].len + 1) {
        aut[cur_v].link = q;
        last = cur_v;
        return;
    }
    ll clone = aut.size();
    aut.push_back(node());
    aut[clone].len = aut[p].len + 1;
    aut[clone].to = aut[q].to, aut[clone].link = aut[q].link;
    aut[q].link = aut[cur_v].link = clone;

    while (p != -1 && aut[p].to[c - 'a'] == q) {
        aut[p].to[c - 'a'] = clone;
        p = aut[p].link;
    }

    last = cur_v;
}

signed main() {
    string s;
    ll k;
    cin >> s >> k;

    vector<node> aut;
    aut.push_back(node());
    ll last = 0;

    for (auto c: s) enhance_aut(aut, c, last);
    dfs(aut, 0);

    k = min(k, aut[0].num_of_paths - 1);

    ll cur_v = 0;
    while (k) {
        for (char c = 'a'; c <= 'z'; ++c) {
            if (aut[cur_v].to.contains(c - 'a')) {
                ll son = aut[cur_v].to[c - 'a'];
                if (aut[son].num_of_paths < k) k -= aut[son].num_of_paths;
                else {
                    cout << c;
                    cur_v = son;
                    --k;
                    break;
                }
            }
        }
    }
}
