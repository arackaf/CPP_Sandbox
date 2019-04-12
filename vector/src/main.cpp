#include <iostream>
#include "myVector.cpp"
#include "thing.cpp"


using std::cout;
using std::endl;

int main(int argc, const char * argv[]) {
    MyVector<Thing> intVector({1, 2, 3});
    
    intVector.push_back(4);
//    intVector.push_back(5);
//    intVector.push_back(6);
//    intVector.push_back(7);
    intVector.forEach([](Thing &val) { cout<<val.val(); });
    cout<<"PUSH_BACK DONE"<<endl<<endl;

    MyVector<Thing> intVectorE({1, 2, 3});
    
    intVectorE.emplace_back(4);
    intVectorE.emplace_back(5);
    intVectorE.emplace_back(6);
    intVectorE.emplace_back(7);
    intVectorE.forEach([](Thing &val) { cout<<val.val(); });
    cout<<"EMPLACE_BACK DONE"<<endl<<endl;
    
    Thing *oneThing = new Thing(1);
    
    Thing *twoThings = new Thing[2]{Thing(1), Thing(2)};
    
    Thing twoThingsB[] = {Thing(3), Thing(4)};
    
    cout<<oneThing->val()<<endl;
    
    cout<<twoThings->val()<<(twoThings + 1)->val()<<endl;
    
    cout<<twoThings[0].val()<<twoThings[1].val()<<endl;
    
    cout<<twoThingsB[0].val()<<twoThingsB[1].val()<<endl;
    
    cout<<endl<<endl;
    
    intVector.forEach([](Thing &val) { cout<<val.val(); });
    cout<<endl;
    
    intVector.forEach([](Thing &val, size_t index) { cout<<index<<" - "<<val.val()<<endl; });
    cout<<endl;
    
    //cout<<intVector[0].val()<<intVector[1].val()<<intVector[2].val()<<endl;
    
    //intVector[1] = 99;
    
    //cout<<intVector[0].val()<<intVector[1].val()<<intVector[2].val()<<endl;

    return 0;
}
