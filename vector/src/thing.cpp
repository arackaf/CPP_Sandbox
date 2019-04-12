#include <stdio.h>
#include <iostream>

using std::endl;
using std::cout;

class Thing {
public:
    Thing(int val): data(val){}
    
    int val(){
        return data;
    }
    ~Thing(){
        cout<<"Destroy me, daddy"<<std::endl;
    }
    
private:
    int data;
};
