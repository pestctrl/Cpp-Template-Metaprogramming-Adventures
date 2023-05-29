#ifndef MATH_H
#define MATH_H

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
struct Add { };

template<typename I>
struct Add<I,Zero>
{
  typedef I result;
};

template<typename I, typename J>
struct Add<I,Succ<J>>
{
  typedef typename Add<Succ<I>,J>::result result;
};

template<typename I, typename J>
struct Mult { };

template<typename I, typename K>
struct Mult<I, Succ<K>>
{
  // not typedef typename Add<I,Mult<I,K>::result>::result result;
  typedef typename Add<I,typename Mult<I,K>::result>::result result;
};

template<>
struct Mult<Succ<Zero>,Zero>
{
  typedef Zero result;
};

template<>
struct Mult<Zero,Succ<Zero>>
{
  typedef Zero result;
};

template<typename T>
struct Mult<T,Zero>
{
  typedef Zero result;
};

template<typename T>
struct Mult<Zero,T>
{
  typedef Zero result;
};

template<typename N>
struct Factorial { };

template<typename N>
struct Factorial<Succ<N>>
{
  typedef typename Mult<Succ<N>,typename Factorial<N>::result>::result result;
};

template<>
struct Factorial<Zero>
{
  typedef Succ<Zero> result;
};

void math_asserts();

#endif
