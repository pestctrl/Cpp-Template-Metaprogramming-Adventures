#include "math.h"
// Helpers
template<int N>
struct Num
{
  Succ<typename Num<N-1>::result> typedef result;
};

template<>
struct Num<0>
{
  Zero typedef result;
};
