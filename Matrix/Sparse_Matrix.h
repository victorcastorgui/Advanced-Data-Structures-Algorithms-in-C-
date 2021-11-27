

#ifndef Sparse_Matrix_h
#define Sparse_Matrix_h

#include "Matrix.h"

#include <list>
#include <iterator>
#include <math.h>
#include <iostream>
#include <sstream>
#include <vector>


using namespace std;

template <typename T>
class Sparse_Matrix {
private:
    struct Node {
        size_t _col;
        T _val;
        
        Node(size_t c = 0, T v = T()) : _col(c), _val(v) {}
        size_t get_col() const { return _col; }
        const T get_value() const { return _val; }
        void set_value(const T &val) { _val = val; }
        virtual const T &operator=(const T& val) { return _val = val;}
        
        friend ostream& operator<<(ostream& os, const Node &node) {
            return os << "{ C: " << node._col << ", V: " << node._val << "}";
        }
    };
    
    vector<list<Node>> _rows;
    size_t _num_rows, _num_cols;
    T _default_val;
    
public:
    Sparse_Matrix(size_t nr = 0, size_t nc = 0, const T &default_val = T()) :
    _num_rows(nr), _num_cols(nc), _default_val(default_val) {
        _rows.resize(nr);
    }

        size_t get_num_rows() const { return _num_rows; }
        size_t get_num_cols() const { return _num_cols; }
        
        bool is_valid(size_t r, size_t c) const {
            if (r >= get_num_rows()) return false;
            if (c >= get_num_cols()) return false;
            return true;
        }
        
        void clear() {
            for(size_t r=0; r < get_num_rows(); r++) {
                _rows[r].clear();
            }
        }
        
        const T get(size_t r, size_t c) const {
            if(!is_valid(r,c)){
                return _default_val;
            }
            
            for (auto &lol: _rows[r]) {
                if (lol._col == c) {
                    return lol._val;
                }
            }
            return _default_val;
        }
        
        bool set(size_t row, size_t col, const T& val) {
            typename std::list<Node>::iterator gob = _rows[row].end();
            if (!is_valid(row , col)) return false;
            
            for (auto it = _rows[row].begin(); it != _rows[row].end(); it++) {
                if (it->_col > col) {
                    gob = it;
                    break;
                }
                
                if (it->_col == col) {
                    if (fabs(val-_default_val) < 0.0000000001) {
                        _rows[row].erase(it);
                        return true;
                    }
                    it->_val = val;
                    return true;
                }
            }
            Node done(col,val);
            _rows[row].insert(gob,done);
            return true;
        }
        
        Matrix <T> get_slice(size_t r1, size_t c1, size_t r2, size_t c2) const {
            if (r1 > r2) swap(r1,r2);
            if (c1 > c2) swap(c1,c2);
            
            Matrix <T> flipSwitch(r2-r1+1,c2-c1+1);
            for (size_t i = 0; i < r2-r1; i++) {
                for (size_t z = 0; z <c2-c1; z++) {
                    flipSwitch.at(i,z) = get(r1+i,c1+z);
                }
            }
            return flipSwitch;
        }
        string to_string() const {return "";}
        
    friend class Tests;
    friend class Mx;
    
};


#endif /* Sparse_Matrix_h */
