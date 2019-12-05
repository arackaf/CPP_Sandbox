namespace rstl
{

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
  Head val;
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