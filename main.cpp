#include <vector>
#include <initializer_list>
#include <iostream>

#include "tuple/tuple.h"

using namespace rstl::Tuple;

using std::cout;
using std::endl;

struct Junk
{
};

int main(int argc, const char *argv[])
{
    tuple t1 = make_tuple(1, 7.2, 9.3f);

    double d = get<1>(t1);
    auto f = get<2>(t1);

    std::cout << ((d == 7.2) ? "true" : "false") << ((d == 7) ? "true" : "false") << std::endl;
    std::cout << ((f == 9.3f) ? "true" : "false") << ((f == 9) ? "true" : "false") << std::endl;

    std::cout << get<0>(t1) << " " << get<1>(t1) << " " << get<2>(t1);

    return 0;
}
