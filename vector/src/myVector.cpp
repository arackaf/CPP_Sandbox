#include <iostream>
#include <vector>
#include <functional>
using std::vector;
using std::cout;
using std::endl;

template<typename T>
class MyVector {
public:
    MyVector(size_t size){
        currentSize = size;
        maxSize = currentSize * 2;
        currentMembers = operator new[](maxSize * sizeof(T));
    }
    MyVector(const std::initializer_list<T> &items){
        currentSize = items.size();
        maxSize = currentSize * 2;
        currentMembers = operator new[](maxSize * sizeof(T));
        
        typename std::initializer_list<T>::iterator it;
        int i = 0;
        for (it = items.begin(); it != items.end(); ++it){
            new((T*)currentMembers + i++) T(*it);
        }
    }
    
    MyVector& push_back(const T& item){
        sizeAsNeeded();
        //TODO: this can't be right, can it?
        (*this)[currentSize++] = item;
        return *this;
    }
    
    template<typename ...Args>
    MyVector& emplace_back(Args&& ...args){
        sizeAsNeeded();
        new((T*)currentMembers + currentSize++) T(args...);
        return *this;
    }

    MyVector filter(std::function<bool(T&)>){
        return ((T*)currentMembers)[index];
    }
    
    T& operator[](size_t index){
        return ((T*)currentMembers)[index];
    }
    
    void forEach(std::function<void(T&)> f){
        for (size_t i = 0; i < currentSize; i++){
            f((*this)[i]);
        }
    }
    
    void forEach(std::function<void(T&, size_t)> f){
        for (size_t i = 0; i < currentSize; i++){
            f((*this)[i], i);
        }
    }
    
private:
    size_t maxSize;
    size_t currentSize;
    void *currentMembers;
    
    void sizeAsNeeded(){
        if (maxSize != currentSize){
            return;
        }
        size_t newMaxSize = maxSize * 2;
        void *newMembers = operator new[](newMaxSize * sizeof(T));
        
        for (size_t i = 0; i < currentSize; i++){
            new((T*) newMembers + i) T((*this)[i]);
            (*this)[i].~T();
        }
        operator delete[](currentMembers);
        currentMembers = newMembers;
    }
};

