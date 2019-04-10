//
//  main.cpp
//  pointers
//
//  Created by Adam Rackis on 4/2/19.
//  Copyright © 2019 Adam Rackis. All rights reserved.
//

#include <iostream>
#include "myVector.cpp"
#include "dumbNumber.cpp"
#include "smartNumber.cpp"

using std::cout;

int main(int argc, const char * argv[]) {
    MyVector<int> intVector({1, 2, 3});
    cout<<intVector[0]<<intVector[1]<<intVector[2]<<std::endl;
    
    
    return 0;
}
