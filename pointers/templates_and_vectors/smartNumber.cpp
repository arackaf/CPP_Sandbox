#include <stdio.h>


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
        return SmartNumber(this + rhs.value);
    }
private:
    T value;
};
