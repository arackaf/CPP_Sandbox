#include <iostream>
#include <vector>
using std::vector;

template<typename T>
class Base {
public:
    Base(const std::initializer_list<T> &items):data(items){}
protected:
    vector<T> data;
};

template <typename T>
class Sub: public Base<T> {
public:
    Sub(std::initializer_list<T> items): data(items), Base<T>(items){}
    
    T sum(){
        T total = 0;
        for (auto i = 0; i < data.size(); i++){
            total += data[i];
            //total = total + data[i];
            //total = data[i] + total;
        }
        return total;
    }
private:
    vector<T> data;
};


