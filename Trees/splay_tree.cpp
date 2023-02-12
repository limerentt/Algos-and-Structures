#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

struct node {
    ll value;
    ll sum;
    node *left;
    node *right;
    node* parent;

    explicit node(ll val) {
        value = val;
        sum = val;
        right = nullptr;
        left = nullptr;
        parent = nullptr;
    }
};

class BSTST {                                                   // Binary Search Tree Splay Tree
    node *root = nullptr;

    static ll get_sum(node *v) {
        if (v == nullptr)
            return 0;
        else
            return v->sum;
    }

    static void sum_fix(node *v) {
        if (v == nullptr)
            return;
        v->sum = get_sum(v->left) + get_sum(v->right) + v->value;
    }

    void clear(node *v) {
        if (v == nullptr)
            return;
        clear(v->left);
        clear(v->right);
        delete v;
    }

    static bool has_parent(node* v) {
        if (v == nullptr)
            return false;
        if (v->parent == nullptr)
            return false;
        return true;
    }

    static bool has_granny(node* v) {
        if (v == nullptr)
            return false;
        if (v->parent == nullptr)
            return false;
        if (v->parent->parent == nullptr)
            return false;
        return true;
    }

    static bool left_son(node* son, node* parent) {
        if (!has_parent(son))
            return false;
        if (son->parent != parent)
            return false;
        if (parent->left != son)
            return false;
        return true;
    }

    static bool right_son(node* son, node* parent) {
        if (!has_parent(son))
            return false;
        if (son->parent != parent)
            return false;
        if (parent->right != son)
            return false;
        return true;
    }

    static void small_rotation(node* v) {
        if (!has_parent(v))
            return;
        node* parent = v->parent;

        if (has_parent(parent)) {
            if (left_son(parent, parent->parent))
                parent->parent->left = v;
            else
                parent->parent->right = v;
        }
        node* grand = parent->parent;

        if (left_son(v, parent)) {
            if (v->right)
                v->right->parent = parent;
            parent->left = v->right;
            v->right = parent;
        } else {
            if (v->left)
                v->left->parent = parent;
            parent->right = v->left;
            v->left = parent;
        }

        v->parent = grand;
        parent->parent = v;

        sum_fix(parent);
        sum_fix(v);
    }

    static void big_rotation(node* v) {
        if (!has_granny(v))
            return;
        if (left_son(v, v->parent) && left_son(v->parent, v->parent->parent) ||
            right_son(v, v->parent) && right_son(v->parent, v->parent->parent)) {
            small_rotation(v->parent);
        } else {
            small_rotation(v);
        }
        small_rotation(v);
    }

    void splay(node* v) {
        if (v == nullptr)
            return;
        while (has_parent(v)) {
            if (has_granny(v))
                big_rotation(v);
            else
            small_rotation(v);
        }
        root = v;
    }

    node* next(ll val) {
        node *v = root;
        node *needed = nullptr;
        while (v != nullptr) {
            if (v->value >= val && (needed == nullptr || v->value < needed->value))
                needed = v;
            if (v->value == val)
                break;
            else if (v->value > val)
                v = v->left;
            else
                v = v->right;
        }
        return needed;
    }

    void split(ll val, node* &left_root, node* &right_root) {
        if (root == nullptr) {
            left_root = right_root = nullptr;
            return;
        }
        right_root = next(val);
        splay(right_root);
        if (right_root == nullptr) {
            left_root = root;
            return;
        }
        left_root = right_root->left;
        if (left_root != nullptr) {
            left_root->parent = nullptr;
            right_root->left = nullptr;
        }
        root = nullptr;
        sum_fix(left_root);
        sum_fix(right_root);
    }

    node* merge(node* left, node* right){
        if (left == nullptr)
            return right;
        if (right == nullptr)
            return left;

        BSTST right_subtree(right);

        node* min_right = right;
        while (min_right->left != nullptr) {
            min_right = min_right->left;
        }

        right_subtree.splay(min_right);
        left->parent = min_right;
        min_right->left = left;
        root = min_right;
        sum_fix(root);
        return root;
    }

public:

    BSTST() = default;

    explicit BSTST(node *root): root(root) {}

    ~BSTST() = default;

    void insert(ll val) {
        node* left;
        node* right;
        split(val, left, right);
        node* new_root = nullptr;
        if (right == nullptr || right->value != val)
            new_root = new node(val);
        root = merge(merge(left, new_root), right);
    }

    ll sum(ll l, ll r) {
        node* left = nullptr;
        node* mid = nullptr;
        node* right = nullptr;

        split(l, left, mid);
        BSTST summing(mid);
        summing.split(r + 1, mid, right);
        ll needed_sum = get_sum(mid);
        root = merge(left, merge(mid, right));
        return needed_sum;
    }
};


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    BSTST tree;
    char read, prev_char;
    ll n, input1, input2, prev_sum;
    std::cin >> n;
    prev_char = '+';

    while(n--) {
        std::cin >> read >> input1;
        if (read == '+') {
            if (prev_char == '?')
                tree.insert((input1 + prev_sum) % 1000000000);
            else
                tree.insert(input1);
            prev_char = '+';
        } else {
            std::cin >> input2;
            prev_sum = tree.sum(input1, input2);
            std::cout << prev_sum << '\n';
            prev_char = '?';
        }
    }
}
