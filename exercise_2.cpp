#include <type_traits>
#include <cstdint>
#include <vector>

template <typename T, typename S>
constexpr bool same = std::is_same<std::decay_t<T>, std::decay_t<S>>::value;

template <class...>
struct are_same;

template <bool B, typename... Args>
struct bool_same : std::false_type {};

template <>
struct bool_same<true> : std::true_type {};

template <typename... Args>
struct bool_same<true, Args...> : are_same<Args...> {};

template <typename T, typename S>
struct are_same<T, S> : bool_same<same<T, S>> {};

template <typename T, typename S, typename... Tail>
struct are_same<T, S, Tail...> : bool_same<same<T, S>, S, Tail...> {};

template <typename... Types>
constexpr bool are_same_v = are_same<Types...>::value;

int main()
{
    static_assert(are_same_v<int, int32_t, signed int>,  "compile assert");
    static_assert(are_same_v<int&, int32_t, const signed int>,  "compile assert");
    static_assert(are_same_v<int*, signed int*>,  "compile assert");
    static_assert(are_same_v<std::vector<int>, std::vector<int>&>,  "compile assert");
    return 0;
}
