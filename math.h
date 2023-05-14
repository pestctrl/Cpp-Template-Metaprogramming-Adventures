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

void math_asserts();
