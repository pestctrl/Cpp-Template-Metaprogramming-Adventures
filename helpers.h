#include "math.h"
// Helpers
template<int N>
struct Num
{
  typedef Succ<typename Num<N-1>::result> result;
};

template<>
struct Num<0>
{
  typedef Zero result;
};
