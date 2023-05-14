#include "math.h"
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
