#ifndef RBT_CPP
#define RBT_CPP

enum Color { RED, BLACK };

template <typename T>
struct Node {
    T val;
    Color color;
    Node<T>* left;
    Node<T>* right;
    Node<T>* parent;

    Node(Color color): color(color) {}
    Node(T val) : val(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

template <typename T>
class RBT {
private:
    Node<T>* root;
    Node<T>* nil;

    void left_rotate(Node<T>* x);
    void right_rotate(Node<T>* x);
    void insert_fixup(Node<T>* node);
    void remove_fixup(Node<T>* node);

    Node<T>* insert(Node<T>* root, Node<T>* node);
    Node<T>* get_min(Node<T>* node);
    Node<T>* get_max(Node<T>* node);
    int get_height(Node<T>* node);
    Node<T>* remove(Node<T>* node);
    Node<T>* get_predecessor(Node<T>* node, T val);
    Node<T>* get_successor(Node<T>* node, T val);
    void print_in_order(Node<T>* node);
    void transplant(Node<T>* u, Node<T>* v);
public:

    RBT();
    void insert(T val);
    void remove(T val);
    T get_min();
    T get_max();
    int get_height();
    T get_predecessor(T val);
    T get_successor(T val);
    void print_in_order();
};

#include "rbt.cpp"
#endif
