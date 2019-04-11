#include <iostream>
#include <vector>
#include <functional>
using std::vector;

template<typename T>
class MyVector {
public:
    MyVector(const std::initializer_list<T> &items){
        currentSize = items.size();
        maxSize = currentSize * 2;
        currentMembers = operator new[](currentSize * sizeof(T));
        
        typename std::initializer_list<T>::iterator it;
        int i = 0;
        for (it = items.begin(); it != items.end(); ++it){
            new((T*)currentMembers + i++) T(*it);
        }
    }
    
    T& operator[](size_t index){
        return *(((T*)currentMembers) + index);
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
};


