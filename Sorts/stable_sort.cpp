#include <iostream>
#include <vector>

using ll = long long;

ll min(ll a, ll b) {
  if (a >= b)
    return b;
  else
    return a;
}

ll five_median(ll a1, ll a2, ll a3, ll a4, ll a5) {
  if (a1 > a2) std::swap(a1, a2);
  if (a4 > a5) std::swap(a4, a5);
  if (a1 > a4) {
    std::swap(a1, a4);
    std::swap(a2, a5);
  }
  if (a2 > a3) {
    if (a3 > a4)
      return min(a3, a5);
    else
      return min(a2, a4);
  } else {
    if (a2 < a4)
      return min(a3, a4);
    else
      return min(a2, a5);
  }
}

void partition(std::vector<ll>& v, std::vector<ll>& medians, ll left, ll right,
               ll* first_eq_piv, ll* first_gr_piv, ll pivot) {
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

ll kth(std::vector<ll>& v, std::vector<ll>& medians, ll left, ll right,
       ll* first_eq_piv, ll* first_gr_piv, ll k) {
  if (right == left) return v[left];
  ll m;
  if (right - left >= 4) {
    for (int i = left; i <= right; i += 5) {
      medians.push_back(
          five_median(v[i], v[i + 1], v[i + 2], v[i + 3], v[i + 4]));
    }
    if ((right - left + 1) % 5 != 0) medians.push_back(v[right]);
    std::vector<ll> med_help;
    m = kth(medians, med_help, 0, medians.size() - 1, first_eq_piv,
            first_gr_piv, medians.size() / 2);
    med_help.clear();
    medians.clear();
  } else {
    m = v[left];
  }

  partition(v, medians, left, right, first_eq_piv, first_gr_piv, m);

  if (*first_eq_piv - left >= k + 1)
    return kth(v, medians, left, *first_eq_piv - 1, first_eq_piv, first_gr_piv,
               k);
  else {
    if (*first_gr_piv - left >= k + 1)
      return m;
    else
      return kth(v, medians, *first_gr_piv, right, first_eq_piv, first_gr_piv,
                 k - (*first_gr_piv - left));
  }
}

void quick_sort(std::vector<ll>& v, std::vector<ll>& medians, ll left, ll right,
                ll* first_eq_piv, ll* first_gr_piv) {
  if (left == right) return;
  partition(v, medians, left, right, first_eq_piv, first_gr_piv,
            kth(v, medians, left, right, first_eq_piv, first_gr_piv,
                (right - left + 1) / 2));
  if (*first_eq_piv != left)
    quick_sort(v, medians, left, *first_eq_piv - 1, first_eq_piv, first_gr_piv);
  if (*first_gr_piv != right + 1)
    quick_sort(v, medians, *first_gr_piv, right, first_eq_piv, first_gr_piv);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  ll n;
  std::cin >> n;

  std::vector<ll> arr, medians;
  ll first_eq_piv = 0, first_gr_piv = 0;

  for (int i = 0; i < n; ++i) {
    ll x;
    std::cin >> x;
    arr.push_back(x);
  }
  quick_sort(arr, medians, 0, n - 1, &first_eq_piv, &first_gr_piv);
  for (int i = 0; i < n; ++i) {
      std::cout << arr[i] << " ";
  }
}
