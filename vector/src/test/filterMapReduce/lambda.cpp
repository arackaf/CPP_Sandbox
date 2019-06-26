#include <iostream>
#include <initializer_list>
#include "../../myVector.cpp"

namespace VectorTest
{

void filterMapLambda()
{
    MyVector<Thing> intVectorFilterMap({1, 2, 3, 4, 5, 6, 7});

    MyVector<Thing> filtered = intVectorFilterMap
                                   .filter([](const Thing &val) { return val.val() % 2 == 0; })
                                   .map([](const Thing &item) { return Thing(item.val() * 2); });

    filtered.forEach([](Thing &item) { cout << item.val() << endl; });
}

void run()
{
    filterMapLambda();
}

} // namespace VectorTest