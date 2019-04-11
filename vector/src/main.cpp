#include <iostream>
#include "myVector.cpp"
#include "thing.cpp"


using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    MyVector<Thing> intVector({1, 2, 3});
    
    
    intVector.forEach([](Thing &val) { cout<<val.val(); });
    cout<<endl;
    
    intVector.forEach([](Thing &val, size_t index) { cout<<index<<" - "<<val.val()<<endl; });
    cout<<endl;
    
    //cout<<intVector[0].val()<<intVector[1].val()<<intVector[2].val()<<endl;
    
    //intVector[1] = 99;
    
    //cout<<intVector[0].val()<<intVector[1].val()<<intVector[2].val()<<endl;

    return 0;
}
