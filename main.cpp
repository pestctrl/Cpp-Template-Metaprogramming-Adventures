#include <iostream>
#include <cassert>
#include <climits>
#include "math.h"
#include "list.h"
#include "helpers.h"
#include "functional.h"
using namespace std;

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

  list_asserts();

  functional_asserts();

  assert((Add<Num<3>::result, Num<2>::result>::result::value == 5));

  assert((Mult<Num<3>::result, Num<2>::result>::result::value == 6));

  assert((Lookup<X, Binding<X, Num<1>::result, EmptyEnv>>::result::value == 1));

  assert((Lookup<X, EmptyEnv>::result::value == INT_MIN));

  assert(Num<3>::result::value == 3);

  assert((Lookup<Y, Binding<X, Num<1>::result,
                            Binding<Y, Num<2>::result, EmptyEnv>>>::result::value == 2));

  std::cout << "SUCCESS!" << std::endl;
}
