#include <iostream>
using namespace std;

#include <functional>
#include <tuple>


namespace detail
{
    template <class F, class Tuple, std::size_t... I>
    constexpr void multyApply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
    {
        ((std::invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t)))),...);
    }
}

template <class F, class Tuple>
constexpr decltype(auto) multyApply(F&& f, Tuple&& t)
{
    detail::multyApply_impl(
        std::forward<F>(f),
        std::forward<Tuple>(t),
        std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
}

int main()
{
    tuple<int, int, int> myTuple(5, 20, 10);
    auto F = [](int &v) { cout << v << endl; };

    multyApply(F, myTuple);

    return 0;
}
