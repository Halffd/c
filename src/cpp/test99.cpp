#include <array>
#include <tuple>
#include <iostream>
#include <utility>
#include <cstring>

template<char Separator>
constexpr auto join(char a) { return std::tuple{a}; }

template<char Separator>
constexpr auto join(char a, char b) { return std::tuple{a, Separator, b}; }

template<char Separator, typename... Args>
constexpr auto join(char a, char b, char c, Args... d) {
 return std::tuple_cat(std::tuple_cat(join<Separator>(a, b), std::tuple{Separator}), join<Separator>(c, d...));
}

template<char... Chars>
constexpr auto operator"" _x() {
 constexpr auto make_array = [](auto... x) { return std::array{x...}; };
 return std::apply(make_array, std::tuple_cat(join<'_'>(Chars...), std::tuple{'\0'}));
}

int main()
{
 auto foo = 12345_x;
 std::puts(foo.data());
}