#include <iostream>
#include <cassert>
using namespace std;

struct Zero
{
  enum { value = 0 };
};

template<typename N>
struct Succ
{
  enum { value = N::value + 1 };
};

template<int N>
struct Factorial
{
  enum { value = N * Factorial<N-1>::value };
};

template<>
struct Factorial<0>
{
  enum { value = 1 };
};

template<typename I,typename J>
struct Add
{ };

template<typename I>
struct Add<I,Zero>
{
  enum { value = I::value };
};

template<typename I, typename J>
struct Add<I,Succ<J>>
{
  enum { value = Add<Succ<I>,J>::value };
};

template<typename I, typename J>
struct Mult
{ };

template<typename I, typename K>
struct Mult<I, Succ<K>>
{
  enum { value = Add<I,Mult<I,K>>::value };
};

template<>
struct Mult<Succ<Zero>,Zero>
{
  enum { value = 0 };
};

template<>
struct Mult<Zero,Succ<Zero>>
{
  enum { value = 0 };
};

template<typename T>
struct Mult<T,Zero>
{
  enum { value = 0 };
};

template<typename T>
struct Mult<Zero,T>
{
  enum { value = 0 };
};

int main() {
  assert(true);

  assert(Zero::value == 0);

  assert(Succ<Zero>::value == 1);

  assert(Factorial<0>::value == 1);

  assert(Factorial<3>::value == 6);

  assert((Mult<Succ<Succ<Succ<Zero>>>,Zero>::value == 0));

  assert((Mult<Zero,Succ<Zero>>::value == 0));

  assert((Mult<Succ<Zero>,Zero>::value == 0));

  assert((Mult<Succ<Succ<Succ<Zero>>>,Succ<Zero>>::value == 3));

  assert((Mult<Succ<Zero>,Succ<Succ<Succ<Zero>>>>::value == 3));

  assert((Mult<Succ<Succ<Succ<Zero>>>,Succ<Succ<Succ<Zero>>>>::value == 9));

  assert((Add<Zero,Succ<Zero>>::value == 1));

  assert((Add<Zero,Succ<Succ<Zero>>>::value == 2));

  assert((Add<Succ<Zero>,Succ<Succ<Zero>>>::value == 3));

  std::cout << "SUCCESS!" << std::endl;
}
