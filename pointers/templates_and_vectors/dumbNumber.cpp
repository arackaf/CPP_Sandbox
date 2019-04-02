#include <stdio.h>

template<typename T>
class DumbNumber {
public:
    DumbNumber(T val): value(val){}
private:
    T value;
};
