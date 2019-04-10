#include <iostream>
#include "myVector.cpp"
#include "thing.cpp"


using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    MyVector<Thing> intVector({1, 2, 3});
    cout<<intVector[0].val()<<intVector[1].val()<<intVector[2].val()<<endl;
    
    intVector[1] = 99;
    
    cout<<intVector[0].val()<<intVector[1].val()<<intVector[2].val()<<endl;

    return 0;
}
