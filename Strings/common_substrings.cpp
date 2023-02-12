// You are given a collection of k strings of lowercase Latin letters. The sum of lengths of these strings is n.
// For an integer i denote l_i as the length of the longest string which is a substring of at least i strings of the initital collection. 
// Calculate l_i for every i from 2 to k. 


#include <bits/stdc++.h>
using namespace std;
using ll = long long;


struct node {
    ll len = 0;
    ll link = -1;
    bool visited = false;
    unordered_map<ll, ll> to;
    set<ll> superstrs;
};

void dfs(vector<node>& aut, ll v) {
    if (aut[v].visited) return;
    aut[v].visited = true;
    for (auto son: aut[v].to) {
        if (son.first < 26) dfs(aut, son.second);
        if (son.first >= 26) aut[v].superstrs.insert(son.first - 25);
        for (auto s: aut[son.second].superstrs) aut[v].superstrs.insert(s);
    }
}

void enhance_aut(vector<node>& aut, ll c, ll& last) {
    ll cur_v = aut.size();
    aut.push_back(node());
    ll p = last;
    if (c >= 26) last = 0;
    else last = cur_v;

    aut[cur_v].len = aut[p].len + 1;

    while (p != -1 && !aut[p].to.contains(c)) {
        aut[p].to[c] = cur_v;
        p = aut[p].link;
    }
    if (p == -1) {
        aut[cur_v].link = 0;
        return;
    }
    ll q = aut[p].to[c];
    if (aut[q].len == aut[p].len + 1) {
        aut[cur_v].link = q;
        return;
    }
    ll clone = aut.size();
    aut.push_back(node());
    aut[clone].len = aut[p].len + 1;
    aut[clone].to = aut[q].to, aut[clone].link = aut[q].link;
    aut[q].link = aut[cur_v].link = clone;

    while (p != -1 && aut[p].to[c] == q) {
        aut[p].to[c] = clone;
        p = aut[p].link;
    }
}

int main() {
    ll k;
    cin >> k;
    string s;

    ll last = 0;

    vector<node> aut;
    aut.push_back(node());

    for (ll i = 1; i <= k; ++i) {
        cin >> s;
        for (auto c: s) enhance_aut(aut, c - 'a', last);
        enhance_aut(aut, 25 + i, last);
    }

    dfs(aut, 0);

    vector<ll> ans(k + 1, ll(0));

    for (const auto& v: aut) {
        ll num = v.superstrs.size();
        ans[num] = max(ans[num], v.len);
    }

    ll last_num = ans[k];
    for (ll i = k; i >= 2; --i) {
        if (ans[i] == 0 || ans[i] < last_num) ans[i] = last_num;
        else last_num = ans[i];
    }

    for (ll i = 2; i <= k; ++i) cout << ans[i] << '\n';
}
