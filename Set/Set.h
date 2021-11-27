

#ifndef Set_h
#define Set_h
#include <vector>
#include <sstream>
#include <sstream>

using namespace std;

template <typename T>
class Set {
private:
    vector<T> *_master_ptr;
    vector<size_t> _elems; // List of indices into this->master
    size_t _sum;
    
public:
    Set(vector<T> *mast_ptr = nullptr) : _master_ptr(mast_ptr), _sum(0){}
    
    const size_t size() const {return _elems.size();}
    const vector <T> *get_master_ptr() const {return _master_ptr;}
    const size_t get_sum() const {return _sum;}
    
    bool add_elem(size_t n){
        if (_master_ptr == nullptr)
            return false; //if gaada apa2
        if (_master_ptr->size() <= n)
            return false; //if sizenya kegedean
        _elems.push_back(n);
        _sum = _sum + _master_ptr->at(n);
        return true;
    }; // n is the index in master
    
    bool add_all_elems(){
        if (_master_ptr == nullptr)
            return false;
        for (size_t i=0; i<_master_ptr->size(); i++) {
            _elems.push_back(i);
            _sum = _sum + _master_ptr->at(i);
        }
        return true;
    }; // Add everything in the master
    
    Set<T> find_biggest_subset_le(size_t target){
        Set<T> playlist(_master_ptr);
        if(target==0){
            return playlist;
        }
        vector<Set<T>> combin;
        combin.emplace_back();
        for (size_t x = 0 ; x < _master_ptr->size(); x++) {
            size_t combinSize = combin.size();
            for(size_t y = 0; y < combinSize; y++) {
                Set<T> keep(_master_ptr); //
                for (size_t z = 0; z < combin[y].size(); z++) {
                    keep.add_elem(combin[y]._elems[z]);
                }
                keep.add_elem(x);
                combin.push_back(keep);
                if (combin.back()._sum == target) {
                    return combin.back();
                }
            }
        }
        //to check biggest num
        size_t maxNum = 0;
        Set<T> maxSet(_master_ptr);
        for (size_t i = 0; i < combin.size(); i++) {
            if ( combin[i]._sum > maxNum && combin[i]._sum < target) {
                maxNum = combin[i]._sum;
                maxSet = combin[i];
            }
        }
        return maxSet;
    };
    
    friend ostream &operator<<(ostream& os, const Set<T> &set) {
        const vector<T> *mast_ptr = set.get_master_ptr();
        os << "{\n";
        for (size_t index : set._elems)
            os << " " << mast_ptr->at(index) << "\n";
        return os << "}";
    }
    
    friend class Tests; // Don't remove this line
};

#endif /* Set_h */
