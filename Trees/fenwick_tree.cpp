#include <iostream>
#include <vector>

using ll = long long;

ll f(ll i) { return i & (i + 1); }

ll g(ll i) { return i | (i + 1); }

class fenwick_tree {
  std::vector<ll> tree;

 public:
  fenwick_tree(std::vector<ll>& a) {
    tree.assign(a.size(), 0);
    for (ll i = 0; i < a.size(); ++i) {
      update(i, a[i]);
    }
  }
  void update(ll index, ll delta);
  ll prefix(ll index);
  ll sum(ll left, ll right);
};

void fenwick_tree::update(ll index, ll delta) {
  for (ll i = index; i < tree.size(); i = g(i)) {
    tree[i] += delta;
  }
}

ll fenwick_tree::prefix(ll index) {
  ll ans = 0;
  for (; index >= 0; index = f(index) - 1) {
    ans += tree[index];
  }
  return ans;
}

ll fenwick_tree::sum(ll left, ll right) {
  if (left == 0) return prefix(right);
  return prefix(right) - prefix(left - 1);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(nullptr);

  ll n, help;
  std::cin >> n;
  std::vector<ll> a(n);
  bool check;

  for (ll i = 0; i < n; ++i) {
    std::cin >> help;
    if (i % 2 == 0)
      a[i] = help;
    else
      a[i] = -help;
  }

  fenwick_tree tree(a);

  ll m, read_first, read_second;
  std::cin >> m;

  while (m--) {
    std::cin >> check >> read_first >> read_second;
    if (check) {
      if (read_first % 2 == 0) {
        std::cout << -tree.sum(read_first - 1, read_second - 1) << '\n';
      } else {
        std::cout << tree.sum(read_first - 1, read_second - 1) << '\n';
      }
    } else {
      if (read_first % 2 == 1) {
        tree.update(read_first - 1, read_second - a[read_first - 1]);
        a[read_first - 1] = read_second;
      } else {
        tree.update(read_first - 1, -(read_second + a[read_first - 1]));
        a[read_first - 1] = -read_second;
      }
    }
  }
}
