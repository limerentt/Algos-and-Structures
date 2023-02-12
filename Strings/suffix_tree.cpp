#include <iostream>
#include <map>
#include <vector>

struct TreeNode {
  std::map<int, int> to;
  int len = 0;
  int start = -1;
  int index = 0;
  bool visited = false;
};

struct SuffTree {
  std::vector<TreeNode> tree;

  SuffTree() {
    tree.push_back(TreeNode());
  }

  void dfsForIndices(int v, int& index) {
    if (tree[v].visited) {
      return;
    }
    tree[v].visited = true;
    tree[v].index = index;
    for (auto son : tree[v].to) {
      tree[son.second].index = index++;
      dfsForIndices(son.second, index);
    }
  }

  void dfsForOutput(int v) {
    if (tree[v].visited) {
      return;
    }
    tree[v].visited = true;
    for (auto son : tree[v].to) {
      if (tree[son.second].visited) {
        continue;
      }
      std::cout << tree[v].index << ' ';
      std::cout << tree[son.second].start << ' ';
      std::cout << tree[son.second].start + tree[son.second].len << '\n';
      dfsForOutput(son.second);
    }
  }
};

struct AutNode {
  int len = 0;
  int link = -1;
  int endpos = 0;
  std::map<int, int> to;
};

struct SuffAut {
  std::vector<AutNode> aut;

  SuffAut() {
    aut.push_back(AutNode());
  }

  void enhanceAut(int c, int& last) {
    int cur_v = aut.size();
    aut.push_back(AutNode());
    aut[cur_v].len = aut[last].len + 1;
    aut[cur_v].endpos = aut[last].endpos + 1;
    int p = last;
    last = cur_v;
    while (p != -1 && aut[p].to.find(c) == aut[p].to.end()) {
      aut[p].to[c] = cur_v;
      p = aut[p].link;
    }
    if (p == -1) {
      aut[cur_v].link = 0;
      return;
    }
    int q = aut[p].to[c];
    if (aut[q].len == aut[p].len + 1) {
      aut[cur_v].link = q;
      return;
    }
    int clone = aut.size();
    aut.push_back(AutNode());
    aut[clone].len = aut[p].len + 1;
    aut[clone].endpos = aut[q].endpos;
    aut[clone].to = aut[q].to, aut[clone].link = aut[q].link;
    aut[q].link = aut[cur_v].link = clone;

    while (p != -1 && aut[p].to[c] == q) {
      aut[p].to[c] = clone;
      p = aut[p].link;
    }
  }

  SuffTree buildTree(std::string& word) {
    SuffTree my_tree;
    my_tree.tree.resize(aut.size(), TreeNode());

    for (int i = 1; i < int(aut.size()); ++i) {
      my_tree.tree[i].start =
        word.size() - (aut[i].endpos - aut[aut[i].link].len);
      my_tree.tree[i].len = aut[i].len - aut[aut[i].link].len;
      my_tree.tree[aut[i].link].to[word[my_tree.tree[i].start] - '$'] = i;
    }
    my_tree.tree[0].start = -1, my_tree.tree[0].len = 0;
    return my_tree;
  }
};

int main() {
  std::string word;
  int last = 0;

  std::cin >> word;

  SuffAut aut;
  for (int i = int(word.size()) - 1; i >= 0; --i) {
    aut.enhanceAut(word[i] - '$', last);
  }

  SuffTree tree = aut.buildTree(word);

  std::cout << tree.tree.size() << '\n';

  int index = 0;
  tree.dfsForIndices(0, index);
  for (auto& v : tree.tree) {
    v.visited = false;
  }
  tree.dfsForOutput(0);
}
