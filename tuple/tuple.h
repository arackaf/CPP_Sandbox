namespace rstl
{

template <typename F>
struct FunctionMetadata {};

template <typename ReturnType, typename ...FuncArgs>
struct FunctionMetadata<ReturnType(*)(FuncArgs...)> {
  using Ret = ReturnType;
};

template <size_t... Is>
struct Index_List{
  constexpr static size_t Size = sizeof...(Is);
};

template <size_t Last, size_t N, template<size_t> typename NextValue, size_t... Is>
struct make_helper{
    using result = typename make_helper<Last + 1, N, NextValue, Is..., NextValue<Last>::Value>::result;
};

template <size_t N, template <size_t> class NextValue, size_t... Is>
struct make_helper<N, N, NextValue, Is...>{
    using result = Index_List<Is...>;
};

template <size_t Last>
struct Increment
{
  constexpr static size_t Value = Last + 1;
};

template <size_t Last>
struct Repeat
{
  constexpr static size_t Value = Last;
};

template <size_t N>
using make_index_list = typename make_helper<0, N - 1, Increment, 0>::result;

template <size_t Value, size_t Count>
using make_repeat_index_list = typename make_helper<0, Count - 1, Repeat, Value>::result;

template <size_t Current, typename CurrentTuple, typename TupleOfTuples, typename Enabled = void, size_t ...Is>
struct make_repeat_from_tuples_helper {
  using result = Index_List<Is...>;
};

template <size_t Current, typename CurrentTuple, typename TupleOfTuples, typename Enabled = void, size_t ...Is>
struct make_range_from_tuples_helper {
  using result = Index_List<Is...>;
};

template<typename CurrentTuple, typename TupleOfTuples>
using tuple_head_empty_with_just_head_after = std::enable_if_t<
  std::is_void_v<typename CurrentTuple::IsTerminal> 
    && 
  std::is_void_v<std::void_t<typename TupleOfTuples::HeadType>>
    &&
  TupleOfTuples::length == 1
>;

template<typename CurrentTuple, typename TupleOfTuples>
using tuple_head_empty_with_more = std::enable_if_t<
  std::is_void_v<typename CurrentTuple::IsTerminal> 
    && 
  std::is_void_v<std::void_t<typename TupleOfTuples::HeadType>>
    &&
  std::is_void_v<std::void_t<typename TupleOfTuples::TailType>>
>;

template<typename CurrentTuple, typename TupleOfTuples>
using tuple_head_empty_with_no_more = std::enable_if_t<
  std::is_void_v<typename CurrentTuple::IsTerminal> 
    && 
  std::is_void_v<TupleOfTuples>
>;

template<typename CurrentTuple>
using tuple_has_more = std::enable_if_t<
  std::is_void_v<std::void_t<typename CurrentTuple::TailType>> 
>;

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <size_t Current, typename CurrentTuple, typename TupleOfTuples, size_t ...Is> 
struct make_repeat_from_tuples_helper<Current, CurrentTuple, TupleOfTuples, tuple_head_empty_with_just_head_after<CurrentTuple, TupleOfTuples>, Is...> {
  using result = typename make_repeat_from_tuples_helper<Current + 1, typename TupleOfTuples::HeadType, void, void, Is..., Current>::result;
};

template <size_t Current, typename CurrentTuple, typename TupleOfTuples, size_t ...Is> 
struct make_repeat_from_tuples_helper<Current, CurrentTuple, TupleOfTuples, tuple_head_empty_with_more<CurrentTuple, TupleOfTuples>, Is...> {
  using result = typename make_repeat_from_tuples_helper<Current + 1, typename TupleOfTuples::HeadType, typename TupleOfTuples::TailType, void, Is..., Current>::result;
};

template <size_t Current, typename CurrentTuple, typename TupleOfTuples, size_t ...Is> 
struct make_repeat_from_tuples_helper<Current, CurrentTuple, TupleOfTuples, tuple_head_empty_with_no_more<CurrentTuple, TupleOfTuples>, Is...> {
  using result = typename make_repeat_from_tuples_helper<Current, void, void, void, Is..., Current>::result;
};

template <size_t Current, typename CurrentTuple, typename TupleOfTuples, size_t ...Is> 
struct make_repeat_from_tuples_helper<Current, CurrentTuple, TupleOfTuples, tuple_has_more<CurrentTuple>, Is...> {
  using result = typename make_repeat_from_tuples_helper<Current, typename CurrentTuple::TailType, TupleOfTuples, void, Is..., Current>::result;
};

template <typename TupleOfTuples>
using make_repeat_index_list_from_tuples = typename make_repeat_from_tuples_helper<0, typename TupleOfTuples::HeadType, typename TupleOfTuples::TailType>::result;

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------

template <size_t Current, typename CurrentTuple, typename TupleOfTuples, size_t ...Is> 
struct make_range_from_tuples_helper<Current, CurrentTuple, TupleOfTuples, tuple_head_empty_with_just_head_after<CurrentTuple, TupleOfTuples>, Is...> {
  using result = typename make_range_from_tuples_helper<0, typename TupleOfTuples::HeadType, void, void, Is..., Current>::result;
};

template <size_t Current, typename CurrentTuple, typename TupleOfTuples, size_t ...Is> 
struct make_range_from_tuples_helper<Current, CurrentTuple, TupleOfTuples, tuple_head_empty_with_more<CurrentTuple, TupleOfTuples>, Is...> {
  using result = typename make_range_from_tuples_helper<0, typename TupleOfTuples::HeadType, typename TupleOfTuples::TailType, void, Is..., Current>::result;
};

template <size_t Current, typename CurrentTuple, typename TupleOfTuples, size_t ...Is> 
struct make_range_from_tuples_helper<Current, CurrentTuple, TupleOfTuples, tuple_head_empty_with_no_more<CurrentTuple, TupleOfTuples>, Is...> {
  using result = typename make_range_from_tuples_helper<Current, void, void, void, Is..., Current>::result;
};

template <size_t Current, typename CurrentTuple, typename TupleOfTuples, size_t ...Is> 
struct make_range_from_tuples_helper<Current, CurrentTuple, TupleOfTuples, tuple_has_more<CurrentTuple>, Is...> {
  using result = typename make_range_from_tuples_helper<Current + 1, typename CurrentTuple::TailType, TupleOfTuples, void, Is..., Current>::result;
};

template <typename TupleOfTuples>
using make_range_index_list_from_tuples = typename make_range_from_tuples_helper<0, typename TupleOfTuples::HeadType, typename TupleOfTuples::TailType>::result;


namespace Tuple
{

template <typename T, typename... Rest>
class tuple
{
public:
  using HeadType = T;
  using TailType = tuple<Rest...>;
  constexpr static size_t length = 1 + tuple<Rest...>::length;

  tuple() {}
  tuple(T head, Rest... tail) : head(head), tail(tail...) {}

  T head;

  tuple<Rest...> tail;
};

template <typename T>
class tuple<T>
{
public:
  using HeadType = T;
  using IsTerminal = void;
  constexpr static size_t length = 1;

  tuple() {}
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