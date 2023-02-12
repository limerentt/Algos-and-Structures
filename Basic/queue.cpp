#include <iostream>

struct node{
    int value = 0;
    node* next = nullptr;
};

class Queue{
    node* tail = nullptr;
    node* mid = nullptr;
    node* nose = nullptr;
    int qsize = 0;
public:
    ~Queue() { clear(); }
    void push(int x);
    void pushmid(int x);
    void pop();
    void clear();
    int back();
};

int Queue::back() {
    return nose -> value;
}

void Queue::push(int x) {
    node* n = new node();
    n -> value = x;
    if (qsize == 0) {
        tail = n;
        mid = n;
        nose = n;
    }
    if (qsize != 0) {
        tail -> next = n;
        tail = n;
        n -> next = nose;
    }
    if (qsize == 1) {
        nose -> next = tail;
    }
    ++qsize;
    if(qsize % 2 == 1 && qsize != 1) {
        mid = mid -> next;
    }
};

void Queue::pushmid(int x) {
    node* n = new node();
    n -> value = x;
    if (qsize == 0) {
        tail = n;
        mid = n;
        nose = n;
    }
    if (qsize != 0) {
        if (qsize == 1) {
            nose -> next = n;
            n -> next = nose;
            mid = nose;
            tail = n;
            nose -> next = tail;
        } else {
            n -> next = mid -> next;
            mid -> next = n;
        }
    }
    ++qsize;
    if (qsize % 2 == 1 && qsize != 1) {
        mid = mid -> next;
    }
};

void Queue::pop() {
    nose = nose -> next;
    delete tail -> next;
    tail -> next = nose;
    --qsize;
    if (qsize % 2 == 1 && qsize != 1) {
        mid = mid -> next;
    }
};

void Queue::clear() {
    while (qsize != 0) {
        nose = nose -> next;
        delete tail -> next;
        tail -> next = nose;
        --qsize;
        if (qsize % 2 == 1 && qsize != 1) {
            mid = mid -> next;
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    Queue q;
    char s;
    int n, k;

    std::cin >> n;

    for (int i = 0; i < n; ++i) {
        std::cin >> s;
        if (s == '+') {
            std::cin >> k;
            q.push(k);
        }
        if (s == '*') {
            std::cin >> k;
            q.pushmid(k);
        }
        if (s == '-') {
            std::cout << q.back() << "\n";
            q.pop();
        }
    }
}
