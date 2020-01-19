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

template <typename... Args>
void doPrintPassthrough(Args&&... args)
{
    doPrint(args...);
}

template <typename Tuple, size_t... Is>
void showTupleVals(const Tuple &t, const rstl::Index_List<Is...> &)
{
    doPrint(get<Is>(t)...);
}

template <typename ...Ts>
void printTuple(const rstl::Tuple::tuple<Ts...> &t)
{
    std::cout<<"Printing Tuple\n\n";
    showTupleVals(t, rstl::make_index_list<rstl::Tuple::tuple<Ts...>::length>{});
}

template <typename TupleA, size_t ...IndexesA, typename TupleB, size_t ...IndexesB>
decltype(auto) tuple_catImpl(TupleA &&tupleA, rstl::Index_List<IndexesA...> &, TupleB &&tupleB, rstl::Index_List<IndexesB...> &)
{
    return rstl::Tuple::make_tuple(rstl::Tuple::get<IndexesA>(tupleA)..., rstl::Tuple::get<IndexesB>(tupleB)...);
}

template <typename TupleA, typename TupleB>
decltype(auto) tuple_cat(TupleA &&tupleA, TupleB &&tupleB)
{
    auto AIndexes = rstl::make_index_list<std::remove_reference_t<TupleA>::length>{};
    auto BIndexes = rstl::make_index_list<std::remove_reference_t<TupleB>::length>{};

    return tuple_catImpl(tupleA, AIndexes, tupleB, BIndexes);
}

template <typename TupleA, typename TupleB, typename ...Rest>
decltype(auto) tuple_cat(TupleA &&tupleA, TupleB &&tupleB, Rest ...rest)
{
    auto AIndexes = rstl::make_index_list<std::remove_reference_t<TupleA>::length>{};
    auto BIndexes = rstl::make_index_list<std::remove_reference_t<TupleB>::length>{};

    return tuple_cat(tuple_catImpl(tupleA, AIndexes, tupleB, BIndexes), rest...);
}

template <size_t ...Is>
decltype(auto) indexListToTuple(rstl::Index_List<Is...> IL)
{
    return make_tuple(Is...);
}

template <typename ...Tuples>
decltype(auto) flatten(Tuples ...tuples)
{
}

template <typename ...Tuples>
decltype(auto) XXX(Tuples ...tuples)
{
    decltype(auto) tupleOfTuples = make_tuple(tuples...);
    decltype(auto) tuplesIndexLists = make_tuple(indexListToTuple(rstl::make_index_list<Tuples::length>{})...);

    //decltype(auto) x = make_tuple(rstl::make_repeat_index_list<tuples)

    //decltype(auto) allTuplesIndexLists = make_tuple(rstl::make_index_list<Tuples::length>{}...);  

    return 0;
    // return XYZ(tuples, tuplesIndexList);  
}




int main(int argc, const char *argv[])
{
    //doPrintPassthrough("Hello", "There", 1, 2, 3, 4.5, "Fool");

    tuple t1 = make_tuple(7.2, 9.3f);

    //double d = get<1>(t1);
    //auto f = get<2>(t1);

    tuple t2 = make_tuple(2.1f, 5);
    
    XXX(t1, t2);

    tuple tCounter = make_tuple(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20);

    printTuple(tuple_cat(t1, t2, make_tuple("one", "two", "C")));

    //showTupleVals(t2, rstl::make_index_list<5>{});

    // std::cout << ((d == 7.2) ? "true" : "false") << ((d == 7) ? "true" : "false") << std::endl;
    // std::cout << ((f == 9.3f) ? "true" : "false") << ((f == 9) ? "true" : "false") << std::endl;

    // std::cout << get<0>(t1) << " " << get<1>(t1) << " " << get<2>(t1);

    return 0;
}
