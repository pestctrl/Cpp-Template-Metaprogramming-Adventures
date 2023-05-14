#include <iostream>
#include <cassert>
#include <climits>
#include "math.h"
using namespace std;

// Helpers
template<int N>
struct GenNumber
{
  Succ<typename GenNumber<N-1>::result> typedef result;
};

template<>
struct GenNumber<0>
{
  Zero typedef result;
};

// Environment MetaValues
struct Error
{
  enum { value = INT_MIN };
};

struct EmptyEnv {};

template<int Name, typename Value, typename Env>
struct Binding {};

// Environment MetaFunctions
template<int Name, typename Env>
struct Lookup {};

template<int Name>
struct Lookup<Name, EmptyEnv>
{
  Error typedef result;
};

template<int Name, typename Value, typename Env>
struct Lookup<Name, Binding<Name, Value, Env>>
{
  Value typedef result;
};

template<int Name1, int Name2, typename Value, typename Env>
struct Lookup<Name1, Binding<Name2, Value, Env>>
{
  typename Lookup<Name1, Env>::result typedef result;
};

enum { X, Y, Z };

int main() {
  assert(true);

  math_asserts();

  assert((Add<GenNumber<3>::result, GenNumber<2>::result>::result::value == 5));

  assert((Mult<GenNumber<3>::result, GenNumber<2>::result>::result::value == 6));

  assert((Lookup<X, Binding<X, GenNumber<1>::result, EmptyEnv>>::result::value == 1));

  assert((Lookup<X, EmptyEnv>::result::value == INT_MIN));

  assert(GenNumber<3>::result::value == 3);

  std::cout << "SUCCESS!" << std::endl;
}
