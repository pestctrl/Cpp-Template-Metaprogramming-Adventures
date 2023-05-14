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
  I typedef result;
};

template<typename I, typename J>
struct Add<I,Succ<J>>
{
  typename Add<Succ<I>,J>::result typedef result;
};

template<typename I, typename J>
struct Mult
{ };

template<typename I, typename K>
struct Mult<I, Succ<K>>
{
  // not typename Add<I,Mult<I,K>::result>::result typedef result;
  typename Add<I,typename Mult<I,K>::result>::result typedef result;
};

template<>
struct Mult<Succ<Zero>,Zero>
{
  Zero typedef result;
};

template<>
struct Mult<Zero,Succ<Zero>>
{
  Zero typedef result;
};

template<typename T>
struct Mult<T,Zero>
{
  Zero typedef result;
};

template<typename T>
struct Mult<Zero,T>
{
  Zero typedef result;
};

int main() {
  assert(true);

  assert(Zero::value == 0);

  assert(Succ<Zero>::value == 1);

  assert(Factorial<0>::value == 1);

  assert(Factorial<3>::value == 6);

  assert((Mult<Succ<Succ<Succ<Zero>>>,Zero>::result::value == 0));

  assert((Mult<Zero,Succ<Zero>>::result::value == 0));

  assert((Mult<Succ<Zero>,Zero>::result::value == 0));

  assert((Mult<Succ<Succ<Succ<Zero>>>,Succ<Zero>>::result::value == 3));

  assert((Mult<Succ<Zero>,Succ<Succ<Succ<Zero>>>>::result::value == 3));

  assert((Mult<Succ<Succ<Succ<Zero>>>,Succ<Succ<Succ<Zero>>>>::result::value == 9));

  assert((Add<Zero,Succ<Zero>>::result::value == 1));

  assert((Add<Zero,Succ<Succ<Zero>>>::result::value == 2));

  assert((Add<Succ<Zero>,Succ<Succ<Zero>>>::result::value == 3));

  std::cout << "SUCCESS!" << std::endl;
}
