#include <iostream>
#include <queue>
#include <vector>

static const int kAlphabetSize = 26;
static const char kStartAlphabet = 'a';
static const char kEndAlphabet = 'z';

struct Node {
  Node() {
    to.assign(kAlphabetSize, -1);
  }
  std::vector<int> to;
  std::vector<int> indices;
  int depth = 0;
  int link = -1;
};

class Trie {
public:
  std::vector<Node> trie;
  Trie() {
    trie.push_back(Node());
  }

  void add(const std::string& proceeding_string, int index) {
    int v = 0;
    for (auto ch : proceeding_string) {
      if (trie[v].to[ch - kStartAlphabet] == -1) {
        trie.push_back(Node());
        trie[v].to[ch - kStartAlphabet] = int(trie.size()) - 1;
      }
      v = trie[v].to[ch - kStartAlphabet];
    }
    trie[v].depth = proceeding_string.size();
    trie[v].indices.push_back(index);
  }

  void ahoKorasik() {
    trie[0].link = 0;
    for (char i = kStartAlphabet; i <= kEndAlphabet; ++i) {
      if (trie[0].to[i - kStartAlphabet] == -1) {
        trie[0].to[i - kStartAlphabet] = 0;
      }
    }
    std::queue<int> q;
    q.push(0);
    while (!q.empty()) {
      int v = q.front();
      q.pop();
      for (int i = 0; i < int(trie[v].to.size()); ++i) {
        int son = trie[v].to[i];
        if (trie[son].link != -1) {
          continue;
        }
        if (v == 0) {
          trie[son].link = 0;
        } else {
          trie[son].link = trie[trie[v].link].to[i];
        }
        for (char c = kStartAlphabet; c <= kEndAlphabet; ++c) {
          if (trie[son].to[c - kStartAlphabet] != -1) {
            continue;
          }
          trie[son].to[c - kStartAlphabet] =
            trie[trie[son].link].to[c - kStartAlphabet];
        }
        q.push(son);
      }
    }
  }

  std::vector<std::vector<int>> countEntrance(int n,
                                              std::string initial_string) {
    std::vector<std::vector<int>> entrances(n);
    int v = 0;
    int u;
    for (int i = 0; i < int(initial_string.size()); ++i) {
      v = trie[v].to[initial_string[i] - kStartAlphabet];
      u = v;
      while (u != 0) {
        for (auto elem : trie[u].indices) {
          entrances[elem].push_back(i - trie[u].depth + 2);
        }
        u = trie[u].link;
      }
    }

    return entrances;
  }
};

int main() {
  std::string initial_string;
  int n;
  std::cin >> initial_string >> n;

  Trie my_trie;

  std::string word;
  for (int i = 0; i < n; ++i) {
    std::cin >> word;
    my_trie.add(word, i);
  }

  my_trie.ahoKorasik();

  std::vector<std::vector<int>> entrances =
    my_trie.countEntrance(n, initial_string);

  for (int i = 0; i < n; ++i) {
    std::cout << entrances[i].size() << ' ';
    for (const auto& index : entrances[i]) {
      std::cout << index << ' ';
    }
    std::cout << '\n';
  }
}
