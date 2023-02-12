#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

ll deg2(ll n) {
    ll counter = 0;
    while ((n >>= 1) && (n > 0)) {
        ++counter;
    }
    return counter;
}

ll middle_of_three(ll a1, ll a2, ll a3)
{
    if ((a1 < a2 && a2 < a3) || (a3 < a2 && a2 < a1))
        return a2;

    if ((a2 < a1 && a1 < a3) || (a3 < a1 && a1 < a2))
        return a1;

    return a3;
}

class sparse_table {
    std::vector<std::vector<std::pair<std::pair<ll, ll>, std::pair<ll, ll>>>> table;
    std::vector<std::pair<ll, ll>> sorted;

public:
    sparse_table(std::vector<ll>& a) {
        table.resize(deg2(a.size()) + 1);
        for (ll i = 0; i < table.size(); ++i) {
            table[i].resize(a.size());
        }
        build(a);
    }
    ll minimum2(ll left, ll right);
    void build(std::vector<ll>& a);
};

void sparse_table::build(std::vector<ll> &a) {
    for (ll i = 0; i < a.size(); ++i) {
        table[0][i] = std::make_pair(std::make_pair(a[i], i), std::make_pair(10000000, -1));
    }

    for (ll k = 0; k < deg2(a.size()); ++k) {
        for (ll i = 0; i + (1 << k) - 1 < a.size(); ++i) {                                                     
            table[k+1][i].first = std::min(table[k][i].first, table[k][i + (1 << k)].first);

            sorted = {table[k][i].first, table[k][i].second, table[k][i + (1 << k)].first,
                      table[k][i + (1 << k)].second};

            std::sort(sorted.begin(), sorted.end());
            table[k+1][i].second = sorted[1];
        }
    }
}

ll sparse_table::minimum2(ll left, ll right) {
    if (left == right)
        return table[0][left].first.first;
    sorted = {table[deg2(right - left + 1)][left].first, table[deg2(right - left + 1)][left].second,
              table[deg2(right - left + 1)][right - (1 << deg2(right - left + 1))+1].first,
              table[deg2(right - left + 1)][right - (1 << deg2(right - left + 1))+1].second};
    std::sort(sorted.begin(), sorted.end());
    if (sorted[0] == sorted[1])
        return std::min(sorted[2], sorted[3]).first;
    return sorted[1].first;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ll n, m;
    std::cin >> n >> m;

    std::vector<ll> a(n);

    for (ll i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    sparse_table table(a);

    ll left, right;

    while(m--) {
        std::cin >> left >> right;
        std::cout << table.minimum2(left - 1, right - 1) << '\n';
    }
}
