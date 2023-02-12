//#include <ext/pb_ds/assoc_container.hpp>
// You are given a string s and n patterns p_i, for each p_i find number of consecutive substrings of s, cyclicly equal to p_i.

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct node {
    ll len = 0;
    ll link = -1;
    ll endpos = 0;
    ll cnt = 0;
    map<ll, ll> to;
};

void enhance_aut(vector<node>& aut, ll c, ll& last) {
    ll cur_v = aut.size();
    aut.push_back(node());
    aut[cur_v].len = aut[last].len + 1;
    aut[cur_v].endpos = aut[last].endpos + 1;
    aut[cur_v].cnt = 1;
    ll p = last;
    last = cur_v;
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
    aut[clone].endpos = aut[q].endpos;
    aut[clone].to = aut[q].to, aut[clone].link = aut[q].link;
    aut[q].link = aut[cur_v].link = clone;

    while (p != -1 && aut[p].to[c] == q) {
        aut[p].to[c] = clone;
        p = aut[p].link;
    }
}

signed main() {
    string s, t;
    ll last = 0;
    ll n;

    cin >> s >> n;

    vector<node> aut;
    aut.push_back(node());

    for (auto c: s) enhance_aut(aut, c - 'a', last);

    vector<pair<ll, ll>> to_sort;

    for (ll i = aut.size() - 1; i >= 0; --i) to_sort.push_back({aut[i].len, i});
    sort(to_sort.begin(), to_sort.end());

    for (ll i = to_sort.size() - 1; i >= 1; --i) aut[aut[to_sort[i].second].link].cnt += aut[to_sort[i].second].cnt;

    for (ll i = 0; i < n; ++i) {
        cin >> t;
        ll t_len = t.size();
        vector<bool> visited(aut.size(), false);
        t += t;
        ll v = 0;
        ll ans = 0;
        ll word_len = 0;
        for (ll j = 0; j < t.size() - 1; ++j) {
            while (!aut[v].to.contains(t[j] - 'a') && aut[v].link != -1) {
                word_len = min(word_len, aut[aut[v].link].len);
                v = aut[v].link;
            }
            v = aut[v].to[t[j] - 'a'], ++word_len;
            word_len = min(word_len, aut[v].len);
            if (!visited[v] && word_len >= t_len) {
                visited[v] = true;
                ans += aut[v].cnt;
            }
            while (aut[v].link != -1 && aut[aut[v].link].len >= t_len - 1) {
                word_len = min(word_len, aut[aut[v].link].len);
                v = aut[v].link;
            }
        }
        cout << ans << '\n';
    }
}
