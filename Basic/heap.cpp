#include <iostream>
#include <string>
#include <vector>

using ll = long long;

class heap {
  std::vector<ll> h, pointer, num;
  ll index;

 public:
  heap() {
    h.push_back(-1);
    pointer.push_back(-1);
    num.push_back(-1);
    index = 0;
  }
  void exchange(ll x, ll y);
  void SiftUp(ll x);
  void SiftDown(ll x);
  void extractMin();
  void decreaseKey(ll x, ll delta);
  void insert(ll x);
  ll getMin();
};

void heap::exchange(ll x, ll y) {
  std::swap(num[x], num[y]);
  std::swap(pointer[num[x]], pointer[num[y]]);
  std::swap(h[x], h[y]);
}

void heap::SiftUp(ll x) {
  while (x != 1) {
    if (h[x] < h[x / 2]) {
      exchange(x, x / 2);
      x /= 2;
    } else
      break;
  }
}

void heap::SiftDown(ll x) {
  while (2 * x <= h.size() - 1) {
    ll y = 2 * x;
    if (2 * x + 1 <= h.size() - 1 && h[2 * x + 1] < h[2 * x]) {
      y = 2 * x + 1;
    }
    if (h[y] < h[x]) {
      exchange(x, y);
      x = y;
    } else
      break;
  }
}

void heap::extractMin() {
  ++index;
  exchange(1, h.size() - 1);
  num.pop_back();
  h.pop_back();
  pointer.push_back(-1);
  if (h.size() > 1) SiftDown(1);
}

void heap::decreaseKey(ll x, ll delta) {
  ++index;
  pointer.push_back(-1);
  h[pointer[x]] -= delta;
  if (h.size() > 1) SiftUp(pointer[x]);
}

void heap::insert(ll x) {
  ++index;
  h.push_back(x);
  num.push_back(index);
  pointer.push_back(h.size() - 1);
  if (h.size() > 1) SiftUp(h.size() - 1);
}

ll heap::getMin() {
  ++index;
  pointer.push_back(-1);
  return h[1];
}

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie(0);

  heap h;

  ll q;
  std::cin >> q;

  std::string read;

  while (q--) {
    std::cin >> read;
    if (read == "insert") {
      ll x;
      std::cin >> x;
      h.insert(x);
    }
    if (read == "getMin") {
      std::cout << h.getMin() << "\n";
    }
    if (read == "extractMin") {
      h.extractMin();
    }
    if (read == "decreaseKey") {
      ll x, delta;
      std::cin >> x >> delta;
      h.decreaseKey(x, delta);
    }
  }
}
