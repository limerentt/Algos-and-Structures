#include <iostream>

using ll = long long;

int digit(ll n, int index) {
  for (int i = 1; i < index; i++) n /= 256;
  return n % 256;
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  ll n;
  std::cin >> n;
  ll num[n + 1], ans[n + 1];
  ll comp[256];

  for (int i = 1; i <= n; ++i) {
    std::cin >> num[i];
  }

  for (int i = 0; i < 256; ++i) {
    comp[i] = 0;
  }

  for (int i = 1; i <= 20; ++i) {
    for (int j = 1; j <= n; ++j) {
      ++comp[digit(num[j], i)];
    }
    for (int j = 1; j < 256; ++j) {
      comp[j] += comp[j - 1];
    }
    for (int j = n; j >= 1; --j) {
      ans[comp[digit(num[j], i)]--] = num[j];
    }
    for (int j = n; j >= 1; --j) {
      num[j] = ans[j];
    }
    for (int i = 0; i < 256; ++i) {
      comp[i] = 0;
    }
  }
  for (int i = 1; i <= n; ++i) std::cout << num[i] << " ";
}
