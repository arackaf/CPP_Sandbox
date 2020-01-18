namespace rstl
{

template <typename F>
struct FunctionMetadata {};

template <typename ReturnType, typename ...FuncArgs>
struct FunctionMetadata<ReturnType(*)(FuncArgs...)> {
  using Ret = ReturnType;
};

template <size_t... Is>
struct Index_List{};

template <size_t Last, size_t N, size_t... Is>
struct make_helper{
    using result = typename make_helper<Last + 1, N, Is..., Last + 1>::result;
};

template <size_t N, size_t... Is>
struct make_helper<N, N, Is...>{
    using result = Index_List<Is...>;
};

template <size_t N>
using make_index_list = typename make_helper<0, N - 1, 0>::result;

namespace Tuple
{

template <typename T, typename... Rest>
class tuple
{
public:
  constexpr static size_t length = 1 + tuple<Rest...>::length;
  tuple(T head, Rest... tail) : head(head), tail(tail...) {}

  T head;

  tuple<Rest...> tail;
};

template <typename T>
class tuple<T>
{
public:
  constexpr static size_t length = 1;

  tuple(T head) : head(head) {}

  T head;
};

template <typename T, typename... Rest>
tuple<T, Rest...> make_tuple(T head, Rest... tail)
{
  return tuple(head, tail...);
}

template <unsigned I, typename Head, typename... Rest>
struct tuple_element
{
  using Type = typename tuple_element<I - 1, Rest...>::Type;
  tuple_element(const tuple<Head, Rest...> &t)
  {
    val = tuple_element<I - 1, Rest...>{t.tail}.val;
  }
  typename tuple_element<I - 1, Rest...>::Type val;
};

template <typename Head, typename... Rest>
struct tuple_element<0, Head, Rest...>
{
  using Type = Head;
  tuple_element(const tuple<Head, Rest...> &t) : val(t.head) {}
  Head val;
};

template <unsigned I, typename... Types>
typename tuple_element<I, Types...>::Type get(const tuple<Types...> &t)
{
  return tuple_element<I, Types...>{t}.val;
}

} // namespace Tuple


// decltype(auto)

template <typename F, typename ...BoundArgs>
class BoundFunction {
  using FuncType = typename FunctionMetadata<F>::Ret;
  F &f;

  using BoundTupleArgs = Tuple::tuple<BoundArgs...>;
  BoundTupleArgs boundArgs;

  public:
  BoundFunction(FuncType f, BoundArgs ...args) : f(f), boundArgs(make_tuple(args...)) {}

  template <typename ...RuntimeArgs>
  FuncType operator() (RuntimeArgs ...args){
    auto X = rstl::make_index_list<BoundTupleArgs::length>();
    return std::apply(f, make_tuple( args...));
  }
};

// template <typename Ret, typename ...Args>
// using ReturnType = 

template<typename F, typename ...Args>
BoundFunction<F, Args...> bind(const F &f, Args ...args)
{
  return 0;
}


} // namespace rstl