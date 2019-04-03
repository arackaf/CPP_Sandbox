#include <stdio.h>
#include <iostream>

template<typename T>
class SmartNumber {
public:
    SmartNumber(T val): value(val){}
    
    operator T() const {
        return this->value;
    }
    
    const T operator+(const SmartNumber<T>& rhs){
        return SmartNumber(this->value + rhs.value);
    }
    const T operator+=(const SmartNumber<T>& rhs){
        SmartNumber<T> result(this->value);
        return result + rhs;
    }
private:
    T value;
};

//template<typename T>
//const T operator += (const T &lhs, const SmartNumber<T> &rhs){
//    std::cout<<"HELLO";
//    return rhs + lhs;
//}
