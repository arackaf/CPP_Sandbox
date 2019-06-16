#include <vector>
#include <initializer_list>
#include <iostream>
#include "myVector.cpp"
#include "thing.cpp"

using std::cout;
using std::endl;

int main(int argc, const char *argv[])
{
    MyVector<int> intVector({1, 2, 3, 4, 5, 6, 7});
    MyVector<Thing> intVectorFilterMap({1, 2, 3, 4, 5, 6, 7});

    MyVector<Thing> filtered = intVectorFilterMap
                                   .filter([](const Thing &val) { return val.val() % 2 == 0; })
                                   .map([](const Thing &item) { return Thing(item.val() * 2); });

    filtered.forEach([](Thing &item) { cout << item.val() << endl; });

    cout << "----------------------------" << endl;

    MyVector<Thing> intVectorFilterMapReduce({1, 2, 3, 4, 5, 6, 7});

    int sum = intVectorFilterMapReduce
                  .filter([](const Thing &val) { return val.val() % 2 == 0; })
                  .map([](const Thing &item) { return Thing(item.val() * 2); })
                  .reduce<int>([](int val, const Thing &item) -> int { return val + item.val(); }, 0);

    cout << "SUM = " << sum << endl
         << endl;

    cout << "----------------------------" << endl;

    auto target = rstl::find(intVector.begin(), intVector.end(), 4);
    if (target != intVector.end())
    {
        cout << "FOUND: " << (*target);
    }
    else
    {
        cout << "NOT FOUND: " << 4;
    }

    target = rstl::find(intVector.begin(), intVector.end(), 99);
    if (target != intVector.end())
    {
        cout << "FOUND: " << (*target);
    }
    else
    {
        cout << "NOT FOUND: " << 99;
    }

    /*
    std::vector<Thing> vT = std::vector<Thing>();
    
    Thing ta = Thing(9);
    Thing tb = Thing(8);
    Thing tc = Thing(7);
    Thing td = Thing(6);
    
    vT.push_back(ta);
    vT[0] = tb;
    vT[0] = tc;
    
    cout<<"------------------"<<endl<<"Done with stl vector"<<endl<<endl;
    
    Thing t1 = Thing(9);
    Thing t2 = Thing(8);
    Thing t3 = Thing(7);
    Thing t4 = Thing(6);
    
    MyVector<Thing> testReplace({});
    
    testReplace[0] = t1;
    testReplace[1] = t1;
    testReplace[2] = t1;
    
    cout<<"_______"<<endl<<endl;
    
    MyVector<Thing> intVector({1, 2, 3});
    
    intVector.push_back(4);
//    intVector.push_back(5);
//    intVector.push_back(6);
//    intVector.push_back(7);
    intVector.forEach([](Thing &val) { cout<<val.val(); });
    cout<<"PUSH_BACK DONE"<<endl<<endl;

    MyVector<Thing> intVectorE({1, 2, 3});
    
    intVectorE.emplace_back(4);
    cout<<"Emplace 4"<<endl;
    intVectorE.emplace_back(5);
    cout<<"Emplace 5"<<endl;
    intVectorE.emplace_back(6);
    cout<<"Emplace 6"<<endl;
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
     
     */

    return 0;
}
