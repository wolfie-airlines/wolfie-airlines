#ifndef CUSTOM_STACK_H
#define CUSTOM_STACK_H
#include <algorithm>
#include <stdexcept>

template<typename T>
class Stack {
    struct StackNode {
        T data;
        StackNode* next;
        explicit StackNode(T d, StackNode* n = nullptr) : data(std::move(d)), next(n) {}
    };

    StackNode* top;

public:
    Stack() : top(nullptr) {}

    ~Stack() {
        while (top) {
            pop();
        }
    }

    void push(T data) {
        top = new StackNode(std::move(data), top);
    }

    T pop() {
        if (!top) throw std::runtime_error("Stos jest pusty");
        StackNode* node = top;
        top = top->next;
        T data = std::move(node->data);
        delete node;
        return data;
    }

    [[nodiscard]] bool isEmpty() const {
        return top == nullptr;
    }
};

#endif //CUSTOM_STACK_H
