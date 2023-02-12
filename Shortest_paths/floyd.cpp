#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ll n;
    cin >> n;
    vector<vector<ll>> weight(n, vector<ll>(n, 0));
    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            cin >> weight[i][j];
        }
    }

    for (ll k = 0; k < n; ++k) {
        for (ll i = 0; i < n; ++i) {
            for (ll j = 0; j < n; ++j) {
                weight[i][j] = min(weight[i][j], weight[i][k] + weight[k][j]);
            }
        }
    }

    for (ll i = 0; i < n; ++i) {
        for (ll j = 0; j < n; ++j) {
            cout << weight[i][j] << " ";
        }
        cout << "\n";
    }
}
