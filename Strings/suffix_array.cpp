#include <iostream>
#include <string>
#include <vector>

static const int kAlphabetSize = 26;

std::vector<int> getParentArray(std::string& word) {
  int n = int(word.size());

  std::vector<int> cnt_start(kAlphabetSize + 1);
  std::vector<int> p(n);
  std::vector<int> c(n);
  for (int i = 0; i < n; ++i) {
    ++cnt_start[word[i] - '`'];
  }
  for (int i = 1; i <= kAlphabetSize; ++i) {
    cnt_start[i] += cnt_start[i - 1];
  }
  for (int i = n - 1; i >= 0; --i) {
    p[--cnt_start[word[i] - '`']] = i;
  }

  int num_of_component = 0;
  for (int i = 1; i < n; ++i) {
    if (word[p[i]] != word[p[i - 1]]) {
      ++num_of_component;
    }
    c[p[i]] = num_of_component;
  }

  std::vector<int> new_c(n);
  std::vector<int> p_old(n);
  std::vector<int> cnt(n);

  int power_of_2 = 1;
  while (power_of_2 < 2 * n) {
    for (int i = 0; i < n; ++i) {
      p_old[i] = (p[i] - power_of_2 + 2 * n) % n;
    }
    for (int i = 0; i < n; ++i) {
      cnt[i] = 0;
    }

    for (int i = 0; i < n; ++i) {
      ++cnt[c[p_old[i]]];
    }
    for (int i = 1; i < n; ++i) {
      cnt[i] += cnt[i - 1];
    }
    for (int i = n - 1; i >= 0; --i) {
      p[--cnt[c[p_old[i]]]] = p_old[i];
    }

    num_of_component = 0;
    new_c[p[0]] = 0;
    for (int i = 1; i < n; ++i) {
      if (c[p[i]] != c[p[i - 1]] ||
          c[(p[i] + power_of_2) % n] != c[(p[i - 1] + power_of_2) % n]) {
        ++num_of_component;
      }
      new_c[p[i]] = num_of_component;
    }
    for (int i = 0; i < n; ++i) {
      c[i] = new_c[i];
    }

    power_of_2 *= 2;
  }
  return p;
}

int main() {
  std::string word;
  std::cin >> word;
  word += '`';

  std::vector<int> p = getParentArray(word);

  for (auto elem : p) {
    if (elem != int(p.size() - 1)) {
      std::cout << elem + 1 << ' ';
    }
  }
}
