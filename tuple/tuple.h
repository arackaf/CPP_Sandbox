namespace rstl
{

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
struct make_index_list{
    using result = typename make_helper<0, N - 1, 0>::result;
};

namespace Tuple
{

template <typename T, typename... Rest>
class tuple
{
public:
  tuple(T head, Rest... tail) : head(head), tail(tail...) {}

  T head;

  tuple<Rest...> tail;
};

template <typename T>
class tuple<T>
{
public:
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

} // namespace rstl