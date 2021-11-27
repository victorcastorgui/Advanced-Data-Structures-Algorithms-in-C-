
#include "Matrix.h"
#include "Sparse_Matrix.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>
#include <math.h>

#pragma once

using namespace std;

class Mx {
    public:
    template <typename T> static bool can_multiply(const Matrix<T> &a, const Matrix<T> &b) {
        if (a.get_num_cols() != b.get_num_rows()) return false;
        else if(a.get_num_rows() == 0) return false;
       else if (a.get_num_cols() == 0) return false;
       else if(b.get_num_rows() == 0) return false;
        else if(b.get_num_cols() == 0) return false;
        
        return true;
    }
    
    template <typename T> static bool multiply(const Matrix<T> &a, const Matrix<T> &b, Matrix<T> &res) {
        if(!can_multiply(a,b)) return false;
        res.resize(a.get_num_rows(),b.get_num_cols());
        size_t cmd = 0;
        for(cmd; cmd < a.get_num_rows(); cmd++) {
            for (size_t dmc = 0; dmc < b.get_num_cols(); dmc++) {
                for(size_t mdc = 0; mdc < a.get_num_cols(); mdc++) {
                    res._rows[cmd][dmc] += a._rows[cmd][mdc]*b._rows[mdc][dmc];
                }
            }
        }
        return true;
    }
    
    template<typename T> static bool can_multiply(const Sparse_Matrix<T> &a, const Sparse_Matrix<T> &b) {
        if (a.get_num_cols() != b.get_num_rows()) return false;
        else if (a.get_num_rows() == 0) return false;
        else if (a.get_num_cols() == 0) return false;
        else if (b.get_num_rows() == 0) return false;
       else if (b.get_num_cols() == 0) return false;
        
        return true;
    }
    
    template<typename T> static bool add_to_cell(Sparse_Matrix<T> &spmat, size_t r, size_t c, const T &val) {
        return spmat.set(r,c,spmat.get(r,c)+val);
    }
    
    template <typename T> static bool multiply(const Sparse_Matrix<T>&a, const Sparse_Matrix<T> &b, Sparse_Matrix<T> &result){
        if(!can_multiply(a,b))
            return false;
        result = Sparse_Matrix<T>(a.get_num_rows(), b.get_num_cols(), 0);
        size_t cmd = 0;
        for(cmd; cmd < a.get_num_rows(); cmd++) {
            for (auto first = a._rows[cmd].begin(); first != a._rows[cmd].end(); first++) {
                for (auto second = b._rows[first->_col].begin(); second != b._rows[first->_col].end(); second++) {
                    add_to_cell(result, cmd, second->_col, ((second->_val)*(first->_val)));
                }
            }
        }
        return true;
    }
    
};

