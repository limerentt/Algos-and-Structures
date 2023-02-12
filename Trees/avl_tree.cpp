#include <iostream>
#include <vector>
#include <algorithm>

using ll = long long;

struct node {
    ll value;
    ll diam;
    node *left;
    node *right;

    explicit node(ll val) {
        value = val;
        diam = 1;
        right = nullptr;
        left = nullptr;
    }
};

class avl {
    node *root = nullptr;
    static const ll bound = 1e9 + 1;


    void clear(node *v) {
        if (v == nullptr)
            return;
        clear(v->left);
        clear(v->right);
        delete v;
    }

    ll nice_abs(node *v) {
        if (v == nullptr)
            return 0;
        else
            return v->diam;
    }

    void diam_fix(node *v) {
        v->diam = std::max(nice_abs(v->left), nice_abs(v->right)) + 1;
    }

    node *rotate_right(node *v) {
        node *w = v->left;
        v->left = w->right;
        w->right = v;
        diam_fix(v);
        diam_fix(w);
        return w;
    }

    node *rotate_left(node *v) {
        node *w = v->right;
        v->right = w->left;
        w->left = v;
        diam_fix(v);
        diam_fix(w);
        return w;
    }

    node *fix2(node *v) {
        diam_fix(v);
        if (nice_abs(v->right) - nice_abs(v->left) == 2) {
            if (nice_abs(v->right->right) < nice_abs(v->right->left))
                v->right = rotate_right(v->right);
            return rotate_left(v);
        }
        if (nice_abs(v->left) - nice_abs(v->right) == 2) {
            if (nice_abs(v->left->right) > nice_abs(v->left->left))
                v->left = rotate_left(v->left);
            return rotate_right(v);
        }
        return v;
    }

    node *insert(ll val, node *vert) {
        if (vert == nullptr) {
            vert = new node(val);
            return vert;
        }
        if (val < vert->value) {
            vert->left = insert(val, vert->left);
        }
        if (val > vert->value) {
            vert->right = insert(val, vert->right);
        }
        vert = fix2(vert);
        return vert;
    }

    node *min(node *v) {
        if (!v->left)
            return v;
        else
            return min(v->left);
    }

    node *after_min(node *v) {
        if (!v->left)
            return v->right;
        v->left = after_min(v->left);
        return fix2(v);
    }

    node *erase(ll val, node *vert) {
        if (vert == nullptr)
            return nullptr;
        if (val < vert->value)
            vert->left = erase(val, vert->left);
        else if (val > vert->value)
            vert->right = erase(val, vert->right);
        else {
            node *left = vert->left;
            node *right = vert->right;

            delete vert;
            if (right == nullptr)
                return left;
            node *help = min(right);
            help->right = after_min(right);
            help->left = left;
            return fix2(help);
        }
        return fix2(vert);
    }

    bool exists(ll val, node *vert) {
        if (vert == nullptr)
            return false;
        if (vert->value == val)
            return true;
        return (exists(val, vert->left) || exists(val, vert->right));
    }

    static ll next(ll val, node *vert, ll bound) {
        if (vert == nullptr)
            return bound;
        else if (vert->value <= val)
            return (next(val, vert->right, bound));
        else
            return (next(val, vert->left, std::min(bound, vert->value)));
    }

    static ll prev(ll val, node *vert, ll bound) {
        if (vert == nullptr)
            return bound;
        else if (vert->value >= val)
            return (prev(val, vert->left, bound));
        else
            return (prev(val, vert->right, std::max(bound, vert->value)));
    }

public:

    avl() = default;

    ~avl() {
        clear(root);
    }

    void insert(ll val) {
        root = insert(val, root);
    }

    void erase(ll val) {
        root = erase(val, root);
    }

    bool exists(ll val) {
        return exists(val, root);
    }

    ll next(ll val) {
        return next(val, root, bound);
    }

    ll prev(ll val) {
        return prev(val, root, -bound);
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    avl tree;
    std::string read;
    ll x;
    while (std::cin >> read) {
        std::cin >> x;
        if (read == "insert")
            tree.insert(x);

        if (read == "delete")
            tree.erase(x);

        if (read == "exists") {
            std::cout << (tree.exists(x) ? "true" : "false") << '\n';
        }

        if (read == "next") {
            if (tree.next(x) == 1000000001)
                std::cout << "none" << '\n';
            else
                std::cout << tree.next(x) << '\n';
        }

        if (read == "prev") {
            if (tree.prev(x) == -1000000001)
                std::cout << "none" << '\n';
            else
                std::cout << tree.prev(x) << '\n';
        }
    }
}
