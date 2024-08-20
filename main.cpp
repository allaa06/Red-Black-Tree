#include "rbt.h"
#include <iostream>

int main() {
    RBT<int> tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    tree.insert(15);
    tree.insert(25);
    tree.insert(5);
    tree.insert(1);



    std::cout << "In-order traversal of the tree:" << std::endl;
    tree.print_in_order();
    std::cout << std::endl;


    std::cout << "Minimum value in the tree: " << tree.get_min() << std::endl;
    std::cout << "Maximum value in the tree: " << tree.get_max() << std::endl;


    std::cout << "Height of the tree: " << tree.get_height() << std::endl;


    int val = 15;
    std::cout << "Predecessor of " << val << ": " << tree.get_predecessor(val) << std::endl;
    std::cout << "Successor of " << val << ": " << tree.get_successor(val) << std::endl;


    tree.remove(10);
    tree.remove(1);
    std::cout << "In-order traversal after removing 10:" << std::endl;
    tree.print_in_order();
    std::cout << std::endl;

    return 0;
}

