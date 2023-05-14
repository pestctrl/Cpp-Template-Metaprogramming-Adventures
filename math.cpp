#include <cassert>
#include "math.h"

void math_asserts()
{
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
}
