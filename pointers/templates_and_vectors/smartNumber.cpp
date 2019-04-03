#include <stdio.h>
#include <iostream>

template<typename T>
class SmartNumber {
public:
    SmartNumber(T val): value(val){}
    
    //friend std::ostream& operator<< (std::ostream& lhs, const SmartNumber<T> &rhs);
    
    const T operator+(const SmartNumber<T>& rhs){
        return SmartNumber(this->value + rhs.value);
    }
    SmartNumber<T>& operator+=(const SmartNumber<T>& rhs){
        this->value = this->value + rhs.value;
        return *this;
    }
    
    T getValue() const{
        return this->value;
    }
private:
    T value;
};

template<typename T>
std::ostream& operator<< (std::ostream& lhs, const SmartNumber<T> &rhs){
    lhs<<rhs.getValue();
    return lhs;
}
