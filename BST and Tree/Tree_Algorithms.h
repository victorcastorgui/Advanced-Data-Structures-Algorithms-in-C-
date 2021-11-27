
#include "BST.h"

#include <cstdlib>
#include <string>
#include <fstream>
#include <regex>
#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>
#include <math.h>


#ifndef Tree_Algorithms_h
#define Tree_Algorithms_h

class Tx{
private: template <typename T> static void _splay(typename BST <T>::Node *&p, const T&x){
    using Node = typename BST<T>::Node;
    if (p -> _data == x) return;
    Node *cur = p;
    Node *left = new Node(T());
    Node *right = new Node(T());
    while(true){
        if ((cur -> _data) < x){
            if ((cur -> _right) == nullptr){
            break;
            }else if ((cur -> _right) -> _data < x){
                if ((cur -> _right) -> _right == nullptr){
                    typename BST<T>::Node *tmp = (cur -> _right);
                    (cur -> _right) = nullptr;
                    typename BST<T>::Node *rxs = left;
                    while(rxs -> _right != nullptr)
                        rxs = (rxs -> _right);
                    (rxs -> _right) = cur;
                    cur = tmp;
                    continue;
                }else{
                    typename BST<T>::Node *tmp = (cur -> _right -> _right);
                    (cur -> _right) -> _right = nullptr;
                    _rotate_with_right_child<T>(cur);
                    typename BST<T>::Node *rxs = left;
                    while(rxs -> _right != nullptr)
                        rxs = (rxs -> _right);
                    (rxs -> _right) = cur;
                    cur = tmp;
                    continue;
                }
            }else{
                typename BST<T>::Node *tmp = (cur -> _right);
                (cur -> _right) = nullptr;
                typename BST<T>::Node *rxs = left;
                while((rxs -> _right) != nullptr) rxs = (rxs -> _right);
                (rxs -> _right) = cur;
                cur = tmp;
                continue;
            }
        }else if ((cur -> _data) > x){
            if ((cur -> _left) == nullptr){
                break;
            }else if ((cur -> _left -> _data) > x){
                    if ((cur -> _left -> _left) == nullptr){
                        typename BST<T>::Node *tmp = (cur -> _left);
                        (cur -> _left) = nullptr;
                        typename BST<T>::Node *rxs = right;
                        while((rxs -> _left) != nullptr) rxs = (rxs -> _left);
                        (rxs -> _left) = cur;
                        cur = tmp;
                        continue;
                    }else{
                        typename BST<T>::Node *tmp = (cur -> _left -> _left);
                        (cur -> _left -> _left) = nullptr;
                        _rotate_with_left_child<T>(cur);
                        typename BST<T>::Node *rxs = right;
                        while(rxs -> _left != nullptr)
                            rxs = (rxs -> _left);
                        (rxs -> _left) = cur;
                        cur = tmp;
                        continue;
                    }
            }else{
                typename BST<T>::Node *tmp = (cur -> _left);
                (cur -> _left) = nullptr;
                typename BST<T>::Node *rxs = right;
                while((rxs -> _left) != nullptr) rxs = (rxs -> _left);
                (rxs -> _left) = cur;
                cur = tmp;
                continue;
                }
            }
        break;
    }
    typename BST<T>::Node *rxs = left;
    while((rxs -> _right) != nullptr)
        rxs = (rxs -> _right);
    (rxs -> _right) = (cur -> _left);
    rxs = right;
    while((rxs -> _left) != nullptr)
        rxs = (rxs -> _left);
    (rxs -> _left) = (cur -> _right);
    (cur -> _left) = (left -> _right);
    (cur -> _right) = (right -> _left);
    delete right;
    delete left;
    left = nullptr;
    right = nullptr;
    p = cur;
    return;
}
    
    template <typename T> static void _rotate_with_left_child(typename BST<T>::Node *&p){
        if (p->_left != nullptr){
            typename BST<T>::Node *temp = p;
            p = p->_left;
            typename BST<T>::Node *rxs = p->_right;
            p->_right = temp;
            temp->_left = rxs;
        }
        return;
    }
    template <typename T> static void _rotate_with_right_child(typename BST<T>::Node *&p){
        if (p->_right != nullptr){
            typename BST<T>::Node *temp = p;
            p = p->_right;
            typename BST<T>::Node *daikin = p->_left;
            p->_left = temp;
            temp->_right = daikin;
        }
        return;
    }
    
public:
    template <typename T> static const T &splay_find(BST<T> &tree, const T &x){
        if(tree._root == nullptr)
            return x;
        _splay(tree._root, x);
        if((tree._root -> _data) == x)
            return (tree._root -> _data);
        return x;
    }
    
    template <typename T> static bool splay_insert(BST<T> &tree, const T &x){
        using Node = typename BST<T>::Node;
        if(tree._root == nullptr) {
            tree._root = new Node(x);
            tree._size++;
            return true;
        }
        _splay(tree._root,x);
        if((tree._root -> _data) == x)
            return false;
        Node *bigMac = new Node(x);
        if(x < (tree._root -> _data)) {
            (bigMac -> _right) = tree._root;
            (bigMac -> _left) = (tree._root -> _left);
            (tree._root -> _left) = nullptr;
        }
        else if(x > (tree._root) -> _data) {
            (bigMac -> _left) = tree._root;
            (bigMac -> _right) = (tree._root -> _right);
            (tree._root -> _right) = nullptr;
        }
        tree._root = bigMac;
        tree._size++;
        return true;
    }
    
    template <typename T> static bool splay_remove(BST<T> &tree, const T &x){
        if(tree._root == nullptr)
            return false;
        _splay(tree._root,x);
        if((tree._root -> _data) != x)
            return false;
        else if((tree._root -> _left) != nullptr) {
            _splay((tree._root -> _left), x);
            (tree._root -> _left) -> _right = (tree._root -> _right);
            (tree._root -> _right) = nullptr;
            tree._root = (tree._root -> _left);
            tree._size--;
            return true;
        }
        tree._root = (tree._root -> _right);
        tree._size--;
        return true;
    }
    
    template <typename T> static bool splay_contains(BST<T> &tree, const T &x){
        return false;
    }
    
    friend class Tests; //Don't remove
};

    

#endif /* Tree_Algorithms_h */
