
#ifndef BST_h
#define BST_h

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

#pragma once

using namespace std;

template <typename T>
class BST {
private:
    struct Node {
        T _data;
        Node *_left, *_right;
        Node(const T &d, Node *l = nullptr, Node *r = nullptr) : _data(d), _left(l), _right(r) {}
    };
    Node *_root;
    size_t _size;
  
    static Node *_deep_copy(const Node *p) {
        if ( p == nullptr )
            return nullptr;
        Node *right = _deep_copy(p -> _right);
        Node *left = _deep_copy(p -> _left);
        Node *temp = new Node((p -> _data), left, right);
        return temp;
    }
    
    bool _insert(Node *&p, const T &elem) {
        if (p == nullptr) {
            p = new Node(elem);
            _size ++;
            return true;
        }
        else if (elem == (p -> _data))
            return false;
        else if (elem < (p -> _data)) {
            if ((p -> _left) != nullptr) {
                return _insert((p -> _left), elem);
            }
            Node *temp = new Node(elem);
            p -> _left = temp;
        }
        else if (elem > (p -> _data)) {
            if ((p -> _right) != nullptr) {
                return _insert((p -> _right), elem);
            }
            Node *temp = new Node(elem);
            (p -> _right) = temp;
        }
        _size++;
        return true;
    }
    
    bool _remove(Node *&p, const T &elem){

        if (p == nullptr)
            return false;
        else if (elem < (p -> _data))
            return _remove((p -> _left), elem);
        else if (elem > (p -> _data))
           return _remove((p -> _right), elem);
        
        else if ((p -> _data) == elem) {
            if ((p -> _right) == nullptr && (p -> _left) == nullptr) {
                delete p;
                p = nullptr;
                _size--;
                return true;
            }
           else if ((p -> _right) == nullptr) {
                Node *remove = p;
                p = (p -> _left);
                delete remove;
                _size--;
                return true;
            }
           else if ((p -> _left) == nullptr) {
                Node *remove = p;
                p = (p -> _right);
                delete remove;
                _size--;
                return true;
            }
            (p -> _data) = (_find_min(p -> _right)) -> _data;
            _remove((p -> _right), (p -> _data));
            return true;
        }
    }
    bool _recursive_delete(Node*&p) {
        if (p == nullptr) return true;
        _recursive_delete((p -> _right));
        _recursive_delete((p -> _left));
        delete p;
        _size--;
        p = nullptr;
        return true;
    }
    const Node *_find_min(Node*p) const {
        if ((p -> _left) != nullptr) {
            return _find_min(p -> _left);
        }
        return p;
    }
    
    Node *_find(Node *p, const T &elem) const {
        if (p == nullptr)
            return nullptr;
        else if (elem < (p -> _data))
            return _find((p -> _left), elem);
        else if (elem > (p -> _data))
            return _find((p -> _right), elem);
        return p;
    }
    
    string _to_string(const Node*p) const {
        return "";
    }
    
public:
    BST() : _root(nullptr), _size(0) {}
    virtual ~BST() { _recursive_delete(_root); }
    
    virtual size_t get_size() const { return _size; }
    
    virtual bool insert(const T &elem) { return _insert(_root, elem); }
    virtual bool remove(const T &elem) { return _remove(_root, elem); }
    
    virtual bool contains(const T &elem) const {return _find(_root, elem) != nullptr; }
    virtual T &find(const T &elem) const {
        Node *phn;
        try{
            phn = _find(_root, elem);
        }
        catch(...){
            return *(new T());
        }
        return (phn -> _data);
    }
    virtual string to_string() const {
        return _to_string(_root);}
    
    class Not_found_exception : public exception {
    public:
        string to_string() { return "Not found exception";}
    };
    
    friend class Tests;
    friend class Tx;
};


#endif /* BST_h */
