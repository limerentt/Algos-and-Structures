#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct node {
    ll len = 0;
    ll link = -1;
    unordered_map<char, ll> to;
};

char to_alpha(char c) {
    if ('a' <= c && c <= 'z') return c;
    else return c + 'a' - 'A';
}

void enhance_aut(vector<node>& aut, char c, ll& last) {
    ll cur_v = aut.size();
    aut.push_back(node());
    aut[cur_v].len = aut[last].len + 1;
    ll p = last;
    while (p != -1 && !aut[p].to.contains(c)) {
        aut[p].to[c] = cur_v;
        p = aut[p].link;
    }
    if (p == -1) {
        aut[cur_v].link = 0;
        last = cur_v;
        return;
    }
    ll q = aut[p].to[c];
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

    while (p != -1 && aut[p].to[c] == q) {
        aut[p].to[c] = clone;
        p = aut[p].link;
    }

    last = cur_v;
}

signed main() {
    vector<node> aut;
    aut.push_back(node());

    string str;
    char operation;
    ll last = 0;

    while (cin >> operation >> str) {
        if (operation == '?') {
            ll v = 0;
            bool exists = true;
            for (auto x: str) {
                x = to_alpha(x);
                if (!aut[v].to.contains(x)) {
                    exists = false;
                    break;
                }
                v = aut[v].to[x];
            }
            if (exists) cout << "YES\n";
            else cout << "NO\n";
        } else if (operation == 'A') {
            for (auto x: str) enhance_aut(aut, to_alpha(x), last);
        }
    }
}
