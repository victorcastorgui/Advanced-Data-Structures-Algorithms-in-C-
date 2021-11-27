
#ifndef Lazy_BST_h
#define Lazy_BST_h

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

template<typename T>

class Lazy_BST{
protected:
    struct Node{
        T _data;
        Node *_left, *_right;
        bool _is_deleted;
        
        Node(const T &d): _data(d), _left(nullptr), _right(nullptr), _is_deleted(false) {}
    };
    Node *_root;
    size_t _size, _real_size;
    bool _recursive_delete(Node *p){
        return false;
    }
    bool _insert(Node *&p, const T &elem){
        if (p == nullptr) {
            p = new Node(elem);
            _size++;
            _real_size++;
            return true;
        }
        else if (elem == p->_data) {
            if (p->_is_deleted) {
                (p->_is_deleted) = false;
                _real_size++;
                return true;
            }
            return false;
        }
        else if (elem < (p->_data)) {
            if ((p->_left) != nullptr) {
                return _insert((p->_left), elem);
            }
            Node *temp = new Node(elem);
            (p->_left) = temp;
        }
        else if (elem > (p->_data)) {
            if ((p->_right) != nullptr) {
                return _insert((p->_right), elem);
            }
            Node *temp = new Node(elem);
            (p->_right) = temp;
        }
        _size++;
        _real_size++;
        return true;
    }
    bool _remove(Node *&p, const T &elem){
        if (p == nullptr) return false;
        else if (elem < (p->_data))
            return _remove((p->_left), elem);
        else if (elem > (p->_data))
            return _remove((p->_right), elem);
        else if (p->_is_deleted)
            return false;
        (p->_is_deleted) = true;
        _size--;
        return true;
    }
    bool _collect_garbage(Node *&p){
        bool lft = false;
        bool rght = false;
        if(p->_left != nullptr)
            lft = _collect_garbage(p->_left);
        else if(p->_right != nullptr)
            rght = _collect_garbage(p->_right);
        else if(p->_is_deleted) {
            _really_remove(p,p->_data);
            return true;
        }
        lft |= rght;
        return lft;
    }
    
    const Node *_find_min(const Node *p) const{ //
        if (p == nullptr)
            return nullptr;
        else if (_find_min(p->_left) != nullptr)
            return _find_min(p->_left);
        else if (!(p->_is_deleted))
            return p;
        else if (_find_min(p->_right) != nullptr)
            return _find_min(p->_right);
        return nullptr;
    }
    
    const Node *_find_real_min(const Node*p) const{
        if (p->_left != nullptr)
            return _find_real_min(p->_left);
        return p;
    }
    
    const Node *_find(const Node *p, const T &elem) const{
        return p;
    }
    
    bool _really_remove(Node *&p, const T &elem){
        if (p == nullptr)
            return false;
        else if (elem < p->_data)
            return _really_remove(p->_left, elem);
        else if (elem > p->_data)
            return _really_remove(p->_right, elem);
        else if (p->_data == elem) {
            if (p->_right == nullptr && p->_left == nullptr) {
                delete p;
                p = nullptr;
                _real_size--;
                return true;
            }
           else if (p->_right == nullptr) {
                Node *reallyRemove = p;
                p = p->_left;
                delete reallyRemove;
                _real_size--;
                return true;
            }
            else if (p->_left == nullptr) {
                Node *reallyRemove = p;
                p = p->_right;
                delete reallyRemove;
                _real_size--;
                return true;
            }
            p->_data = (_find_min(p->_right))->_data;
            _really_remove(p->_right, p->_data);
            return true;
        }
    }
    string _to_string(const Node *p) const{
        return "";
    }
public:
    Lazy_BST() : _root(nullptr), _size(0), _real_size(0) {}
    ~Lazy_BST() { _recursive_delete(_root); }
    
    size_t get_size() const {return _size;}
    size_t get_real_size() const {return _real_size;}
    bool insert(const T &elem){ return _insert(_root, elem);}
    bool remove(const T &elem){ return _remove(_root, elem);}
    bool collect_garbage(){ return _collect_garbage(_root);}
    bool contains(const T &elem) const{ return _find(_root, elem)!=nullptr;}
    const T &find(const T &elem) const{
        return _find(_root, elem)->_data;
    }
    string to_string() const{
        return "";
    }
    bool clear(){
        return false;
    }
    class Not_found_exception : public exception {
    public:
        string what() {
            return "Element not found exception";
        }
    };
    friend class Tests;
};


#endif /* Lazy_BST_h */
