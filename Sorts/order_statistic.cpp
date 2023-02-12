#include <iostream>
#include <vector>

using ll = long long;

void partition(ll v[], ll left, ll right, ll *first_eq_piv, ll *first_gr_piv,
               ll pivot) {
  std::vector<ll> copy;
  for (int i = left; i <= right; ++i) {
    if (v[i] < pivot) {
      copy.push_back(v[i]);
    }
  }
  *first_eq_piv = left + copy.size();
  for (int i = left; i <= right; ++i) {
    if (v[i] == pivot) {
      copy.push_back(v[i]);
    }
  }
  *first_gr_piv = left + copy.size();
  for (int i = left; i <= right; ++i) {
    if (v[i] > pivot) {
      copy.push_back(v[i]);
    }
  }
  for (int i = left; i <= right; ++i) {
    v[i] = copy[i - left];
  }
}

ll kth(ll v[], ll left, ll right, ll *first_eq_piv, ll *first_gr_piv, ll k) {
  ll m = v[(left + right) / 2];

  partition(v, left, right, first_eq_piv, first_gr_piv, m);

  if (*first_eq_piv - left >= k + 1)
    return kth(v, left, *first_eq_piv - 1, first_eq_piv, first_gr_piv, k);
  else {
    if (*first_gr_piv - left >= k + 1)
      return m;
    else
      return kth(v, *first_gr_piv, right, first_eq_piv, first_gr_piv,
                 k - (*first_gr_piv - left));
  }
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  ll n, k;
  std::cin >> n >> k;

  ll arr[n], first_eq_piv = 0, first_gr_piv = 0;

  for (int i = 0; i < n; ++i) {
    std::cin >> arr[i];
  }
  std::cout << kth(arr, 0, n - 1, &first_eq_piv, &first_gr_piv, k);
}
