//Parisa Nawar pxn210032

#ifndef VECTORTEMPLATE_H
#define VECTORTEMPLATE_H

#include <string>
#include <vector>

template<class T> 

class VectorTemplate {
    
    private:
        std::vector<T> store;
        
        
    public:
        VectorTemplate();
        VectorTemplate(std::vector<T>);
        
        void setVector(T a) {store.add(a);}
        
        std::vector<T> getVector() {return store;}
        
        void InsertionSort();
        
        bool BinarySearch(T search);
        
        
        
        
};


template<typename T>
VectorTemplate<T>::VectorTemplate() {
}

template<typename T>
VectorTemplate<T>::VectorTemplate(std::vector<T> vctr) {
    store = vctr;
}

template<typename T>
void VectorTemplate<T>::InsertionSort() {
    
    T temp;
    size_t j;
    
    for(size_t i = 1; i < store.size(); i++) {
        
        temp = store[i];
        j = i - 1;
        
        while(j >= 0 && store[j] > temp) {
            store[j + 1] = store[j];
            j--;
        }
        
        store[j + 1] = temp;
    }
}

template<typename T>
bool VectorTemplate<T>::BinarySearch(T search) {
    
    size_t upper = store.size() - 1;
    size_t lower = 0;
    size_t mid;
    
    while(lower <= upper) {
        mid = (upper + lower) / 2;
        
        if(store[mid] == search) {
            return true;
        }
        else if(store[mid] > search) {
            upper = mid - 1;
        }
        else if(store[mid] < search) {
            lower = mid + 1;
        }
    }

    return false;
}

#endif