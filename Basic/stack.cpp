#include <iostream>
#include <string>

struct node{
    int value;
    node* prev;
};

class Stack{
    node* top = nullptr;
    int size = 0;
public:
    ~Stack() { clear(); }
    void push(int x);
    void pop();
    void clear();
    int size();
    std::string back();
};

void Stack::push(int x) {
    node* n = new node();
    n->value = x;
    n->prev = top;
    top = n;
    ++size;
};

std::string Stack::back() {
    if (top != nullptr)
        return std::to_string(top->value);
    else
        return "error";
};

void Stack::pop() {
    if (top != nullptr) {
        node* n = top->prev;
        delete top;
        top = n;
        --size;
    }
};

void Stack::clear() {
    while (top != nullptr) {
        node* n = top->prev;
        delete top;
        top = n;
        --size;
    }
};

int Stack::size(){
    return razmer;
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);

    Stack s;

    std::string check;
    std::cin >> check;

    while (check != "exit") {
        switch(check) {
          case "push":
              int r;
              std::cin >> r;
              s.push(r);
              std::cout << "ok" << "\n";
          case "pop":
              std::cout << s.back() << '\n';
              s.pop();
          case "back":
              std::cout << s.back() << '\n';
          case "size": 
              std::cout << s.size() << '\n';
          case "clear": 
              s.clear();
              std::cout << "ok" << "\n";
        }
        std::cin >> check;
    }

    if (check == "exit") {
        std::cout << "bye" << "\n";
        s.clear();
        return 0;
    }
}
