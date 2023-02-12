#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct node {
    node() { to.assign(26, -1); }
    vector<int> to;
    vector<int> indices;
    ll depth = 0;
    int link = -1;
};

void add(vector<node>& trie, const string& s, int index) {
    int v = 0;
    for (auto x: s) {
        if (trie[v].to[x - 'a'] == -1) {
            trie.push_back(node());
            trie[v].to[x - 'a'] = int(trie.size()) - 1;
        }
        v = trie[v].to[x - 'a'];
    }
    trie[v].depth = s.size();
    trie[v].indices.push_back(index);
}

void koras(vector<node>& trie) {
    trie[0].link = 0;
    for (char i = 'a'; i <= 'z'; ++i) {
        if (trie[0].to[i - 'a'] != -1) continue;
        else trie[0].to[i - 'a'] = 0;
    }
    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < trie[v].to.size(); ++i) {
            int u = trie[v].to[i];
            if (trie[u].link != -1) continue;
            if (v == 0) trie[u].link = 0;
            else trie[u].link = trie[trie[v].link].to[i];
            for (char c = 'a'; c <= 'z'; ++c) {
                if (trie[u].to[c - 'a'] != -1) continue;
                trie[u].to[c - 'a'] = trie[trie[u].link].to[c - 'a'];
            }
            q.push(u);
        }
    }
}

int main() {
    string start, str;
    int n;

    cin >> start >> n;

    vector<node> trie;
    trie.push_back(node());

    for (int i = 0; i < n; ++i) {
        cin >> str;
        add(trie, str, i);
    }

    koras(trie);

    int v = 0, u;
    vector<vector<int>> ans(n);
    for (int i = 0; i < start.size(); ++i) {
        v = trie[v].to[start[i] - 'a'];
        u = v;
        while (u != 0) {
            for (auto elem: trie[u].indices) ans[elem].push_back(i - trie[u].depth + 2);
            u = trie[u].link;
        }
    }

    for (int i = 0; i < n; ++i) {
        cout << ans[i].size() << ' ';
        for (const auto& elem: ans[i]) cout << elem << ' ';
        cout << '\n';
    }
}
