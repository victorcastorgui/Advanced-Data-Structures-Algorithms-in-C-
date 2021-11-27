

#ifndef Matrix_h
#define Matrix_h

#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <iterator>

#pragma once

using namespace std;

template <typename T>

class Matrix {
protected:

    
public:
    vector<vector<T> > _rows;
    static string to_string_example(T const & x) {
        using std::to_string;
        return to_string(x);
    }
    Matrix(size_t nr = 0, size_t nc = 0){
        resize(nr,nc);
    }
    
    size_t get_num_rows() const { return _rows.size(); };
    size_t get_num_cols() const { return (_rows.size()>0? _rows[0].size() : 0); };
    void clear() { _rows.clear(0); }
    
    void resize(size_t nr, size_t nc) {
        _rows.resize(nr, vector<T>(nc));
    }
    T &at(size_t r, size_t c) {
        if (r >= get_num_rows()) throw OOB_exception();
        if (c >= get_num_cols()) throw OOB_exception();
        
        return _rows[r][c];
    }
    
    string to_string() const {
        string keep = "# Matrix\n";
        for (size_t r = 0; r < get_num_rows(); r++) {
            for (size_t c = 0; c < get_num_cols(); c++) {
                string keepSt = to_string_example(_rows[r][c]);
                if (c != 0) keep += " ";
                if (keepSt.size() < 6) {
                    size_t spaces = 6 - keepSt.size();
                    for (size_t sp = 0; sp < spaces; sp++) {
                        keep += " ";
                    }
                }
                keep += keepSt;
            }
            keep += "\n";
        }
        return keep;
    }
    
    class OOB_exception : public exception {
        public: string what() {return "Out of bounds access"; }
    };
    

    
    friend ostream &operator<<(ostream& os, const Matrix<T> &mat) {
        return os << mat.to_string();
    }
    
    friend bool operator==(const Matrix<T> &m1, const Matrix<T> &m2) {
        if (m1.get_num_rows() != m2.get_num_rows()) return false;
        if (m1.get_num_cols() != m2.get_num_cols()) return false;
        
        for (size_t i = 0; i < m1.get_num_rows(); i++) {
            for (size_t z = 0; z < m1.get_num_cols(); z++) {
                if(m1._rows[i][z] != m2._rows[i][z]) return false;
            }
        }
       
        return true;
    }
    
    friend bool operator!=(const Matrix<T> &m1, const Matrix<T> &m2) {
        return !(m1==m2);
    }
    
    friend class Tests;
};

#endif /* Matrix_h */
