#include <type_traits>

#include "pack.h"

// test cases
using P = Pack<int, double, char, int>;

// size
// initialization
static_assert(P::size == 4);
// check empty pack
static_assert(Pack<>::size == 0);

// index -> type
static_assert(std::is_same_v<P::type<0>, int>);
static_assert(std::is_same_v<P::type<1>, double>);
static_assert(std::is_same_v<P::type<2>, char>);
static_assert(std::is_same_v<P::type<3>, int>);
// P::type<4>;   // fail out of range
// P::type<-1>;  // would fail negative

// type -> index
static_assert(P::index<int> == 0);  // FIRST occurrence, not 3
static_assert(P::index<double> == 1);
static_assert(P::index<char> == 2);
static_assert(P::index<float> == -1);  // not present
static_assert(Pack<>::index<int> == -1);

int main() { return 0; }
