#ifndef RBT_H
#define RBT_H

#include <iostream>
#include "rbt.h"
#include <limits>

template <typename T>
RBT<T>::RBT() {
   nil = new Node<T>(BLACK);
   nil->left = nil;
   nil->right = nil;
   nil->parent = nil;
   root = nil;
}

template <typename T>
void RBT<T>::left_rotate(Node<T>* x)
{
   Node<T>* y = x->right;
   x->right = y->left;

   if(y->left != nil)
   {
      y->left->parent = x;
   }

   y->parent = x->parent;

   if(x->parent ==  nil)
      root = y;
   else if(x == x->parent->left)
   {
      x->parent->left = y;
   }
   else
   {
      x->parent->right = y;
   }
   y->left = x;
   x->parent = y;
    
}

template <typename T>
void RBT<T>::right_rotate(Node<T>* x)
{
   Node<T>* y = x->left;
   x->left = y->right;

   if(y->right != nil)
   {
      y->right->parent = x;
   }

   y->parent = x->parent;

   if(x->parent == nil)
   {
      root = y;
   }
   else if(x ==x->parent->left)
   {
      x->parent->left = y;
   }
   else
   {
      x->parent->right = y;
   }
   y->right = x;
   x->parent = y;
}

template <typename T>
Node<T>* RBT<T>::insert(Node<T>* node, Node<T>* z)
{
   Node<T>* y = nil;
   Node<T>* x = node;

   while(x != nil) {
      y = x;
      if(z->val > x->val) {
         x = x->right;
      }
      else {
         x = x->left;
      }
   }
      z->parent = y;

      if(y == nil) {
         root = z;
      }
      else if(y->val > z->val) {
         y->left = z;
      }
      else {
         y->right = z;
      }
      insert_fixup(z);
   
   return root;
}

template <typename T>
void RBT<T>::remove_fixup(Node<T>* x)
{
  while (x != root && x->color == BLACK) {
        if (x == x->parent->left) {
            Node<T>*w = x->parent->right;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                left_rotate(x->parent);
                w = x->parent->right;
            }

            if (w->left->color == BLACK && w->right->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->right->color == BLACK) {
                    w->left->color = BLACK;
                    w->color = RED;
                    right_rotate(w);
                    w = x->parent->right;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                left_rotate(x->parent);
                x = root;
            }
        } else {
            Node<T> *w = x->parent->left;

            if (w->color == RED) {
                w->color = BLACK;
                x->parent->color = RED;
                right_rotate(x->parent);
                w = x->parent->left;
            }

            if (w->right->color == BLACK && w->left->color == BLACK) {
                w->color = RED;
                x = x->parent;
            } else {
                if (w->left->color == BLACK) {
                    w->right->color = BLACK;
                    w->color = RED;
                    left_rotate(w);
                    w = x->parent->left;
                }

                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                right_rotate(x->parent);
                x = root;
            }
        }
    }
    x->color = BLACK;

}

template <typename T>
void RBT<T>::insert_fixup(Node<T>* z) {
         while (z->parent->color == RED) {
            if (z->parent == z->parent->parent->left) {
                Node<T>* y = z->parent->parent->right;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    right_rotate(z->parent->parent);
                }
            } else {
                Node<T>* y = z->parent->parent->left;
                if (y->color == RED) {
                    z->parent->color = BLACK;
                    y->color = BLACK;
                    z->parent->parent->color = RED;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = BLACK;
                    z->parent->parent->color = RED;
                    left_rotate(z->parent->parent);
                }
            }
        }
        root->color = BLACK;
}

template <typename T>
void RBT<T>::transplant(Node<T>* u, Node<T>* v) {
   if(u->parent == nil) {
      root = v;
   }
   else if(u == u->parent->left) {
      u->parent->left = v;
   }
   else {
      u->parent->right = v;
   }
   v->parent = u->parent;
}

template <typename T>
Node<T>* RBT<T>::remove(Node<T>* z) {
    Node<T> *y = z;
    Node<T> *x;
    Color yOriginalColor = y->color;

    if (z->left == nil) {
        x = z->right;
        transplant(z, z->right);
    } else if (z->right == nil) {
        x = z->left;
        transplant(z, z->left);
    } else {
        y = get_min(z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y != z->right) {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        else {
           x->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (yOriginalColor == BLACK) {
        remove_fixup(x);
    }
    return root;
}

template <typename T>
Node<T>* RBT<T>::get_min(Node<T>* node) {

   if(node == nil)
   {
      return  nil;
   }
   Node<T>* cur = node;
   while(cur->left != nil)
   {
      cur = cur->left;
   }

   return cur;
}

template <typename T>
Node<T>* RBT<T>::get_max(Node<T>* node) {

   if(node == nil) 
   {
      return nil;
   }
   Node<T>* curr = node;
   while(curr->right != nil)
   {
      curr = curr->right;
   }

   return curr;
}

template <typename T>
int RBT<T>::get_height(Node<T>* node) {
   if(node == nil) { return 0; }
   return std::max(get_height(node->left), get_height(node->right)) + 1;

}

template <typename T>
Node<T>* RBT<T>::get_predecessor(Node<T>* node, T val) {
   Node<T>* pred = nil;
   Node<T>* curr = node;
   while (curr->val != val)
   {
      if (curr->val > val)
      {
          curr = curr->left;
      }
      else 
      { 
         pred = curr;
         curr = curr->right;
      }
    }
    if(curr->left != nil)
    {
     return get_max(curr->left);
    }
    return pred;
}

template <typename T>
Node<T>* RBT<T>::get_successor(Node<T>* node, T val) {
   Node<T>* successor = nil;
   Node<T>* curr = node;
   while (curr->val != val)
   {
      if (curr->val <= val)
      {
          curr = curr->right;
      }
      else 
      { 
         successor = curr;
         curr = curr->left;
      }
    }
   if(curr->right != nil)
   {
      return get_min(curr->right);
   }
   return successor;
}

template <typename T>
void RBT<T>::print_in_order(Node<T>* node) {
   if(node == nil) { return; }
   print_in_order(node->left);
   std::cout <<" " << node->val;
   if(node->color)
      std::cout << "Black";
   else
      std::cout << "Red";
   print_in_order(node->right);
}

template <typename T>
void RBT<T>::insert(T val) {
   Node<T>* newNode = new Node<T>(val);
   newNode->left = nil;
   newNode->right = nil;
   newNode->parent = nil;
   root = insert(root, newNode);
}

template <typename T>
void RBT<T>::remove(T val) {
   Node<T>* curr = root;
   while(curr->val != val && curr != nil)
   {
      if(curr->val > val)
         curr = curr->left;
      else
         curr = curr->right;
   }
   root = remove(curr);
}

template <typename T>
int RBT<T>::get_height() {
   return get_height(root);
}

template <typename T>
T RBT<T>::get_min() {
   Node<T>* minNode = get_min(root);
   return (minNode != nil)? minNode->val : std::numeric_limits<T>::min();
}

template <typename T>
T RBT<T>::get_max() {
   Node<T>* maxNode = get_max(root);
   return (maxNode != nil)? maxNode->val : std::numeric_limits<T>::max();
}

template <typename T>
T RBT<T>::get_predecessor(T val) {
    Node<T>* predecessor = get_predecessor(root, val);
    return (predecessor != nil)? predecessor->val : std::numeric_limits<T>::min();
}

template <typename T>
T RBT<T>::get_successor(T val) {
    Node<T>* successor = get_successor(root, val);
    return (successor != nil)? successor->val : std::numeric_limits<T>::max();
}

template <typename T>
void RBT<T>::print_in_order() {
   print_in_order(root);
}

#endif
