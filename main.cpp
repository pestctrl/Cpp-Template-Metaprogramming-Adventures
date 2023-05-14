#include <iostream>
#include <cassert>
#include <climits>
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

template<typename N>
struct Factorial
{ };

template<typename N>
struct Factorial<Succ<N>>
{
  typename Mult<Succ<N>,typename Factorial<N>::result>::result typedef result;
};

template<>
struct Factorial<Zero>
{
  Succ<Zero> typedef result;
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

  assert(Zero::value == 0);

  assert(Succ<Zero>::value == 1);

  assert(Factorial<Zero>::result::value == 1);

  assert(Factorial<Succ<Succ<Succ<Zero>>>>::result::value == 6);

  assert((Mult<Succ<Succ<Succ<Zero>>>,Zero>::result::value == 0));

  assert((Mult<Zero,Succ<Zero>>::result::value == 0));

  assert((Mult<Succ<Zero>,Zero>::result::value == 0));

  assert((Mult<Succ<Succ<Succ<Zero>>>,Succ<Zero>>::result::value == 3));

  assert((Mult<Succ<Zero>,Succ<Succ<Succ<Zero>>>>::result::value == 3));

  assert((Mult<Succ<Succ<Succ<Zero>>>,Succ<Succ<Succ<Zero>>>>::result::value == 9));

  assert((Add<Zero,Succ<Zero>>::result::value == 1));

  assert((Add<Zero,Succ<Succ<Zero>>>::result::value == 2));

  assert((Add<Succ<Zero>,Succ<Succ<Zero>>>::result::value == 3));

  assert((Lookup<X, Binding<X,Succ<Zero>, EmptyEnv>>::result::value == 1));

  assert((Lookup<X, EmptyEnv>::result::value == INT_MIN));

  std::cout << "SUCCESS!" << std::endl;
}
