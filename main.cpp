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

template <typename Arg, typename... Args>
void doPrint(Arg&& arg, Args&&... args)
{
    std::cout << std::forward<Arg>(arg);
    ((std::cout << ',' << std::forward<Args>(args)), ...);
}

template <typename Tuple, size_t... Is>
void showTupleVals(const Tuple &t, const rstl::Index_List<Is...> &)
{
    doPrint(get<Is>(t)...);
}

int main(int argc, const char *argv[])
{
    tuple t1 = make_tuple(1, 7.2, 9.3f);

    double d = get<1>(t1);
    auto f = get<2>(t1);

    tuple t2 = make_tuple(1, 2, 3, 4, 5, 6, 7, 8);

    showTupleVals(t2, rstl::make_index_list<5>::result{});

    // std::cout << ((d == 7.2) ? "true" : "false") << ((d == 7) ? "true" : "false") << std::endl;
    // std::cout << ((f == 9.3f) ? "true" : "false") << ((f == 9) ? "true" : "false") << std::endl;

    // std::cout << get<0>(t1) << " " << get<1>(t1) << " " << get<2>(t1);

    return 0;
}
