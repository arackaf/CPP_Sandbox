//
//  main.cpp
//  pointers
//
//  Created by Adam Rackis on 4/2/19.
//  Copyright © 2019 Adam Rackis. All rights reserved.
//

#include <iostream>
#include "genericAdder.cpp"
#include "dumbNumber.cpp"
#include "smartNumber.cpp"

using std::cout;

int main(int argc, const char * argv[]) {
    Sub<int> sInt({1,2,3,4,5,6,7,8,9,10});
    cout<<sInt.sum()<<std::endl;
    
    Sub<DumbNumber<int>> sDN({2,3,4});
    //show lazy instantiation of template!
    //cout<<sDN.sum(); //compile error!

    Sub<SmartNumber<int>> sSN({2,3,4});
    cout<<sSN.sum()<<std::endl;
    
    
    return 0;
}
