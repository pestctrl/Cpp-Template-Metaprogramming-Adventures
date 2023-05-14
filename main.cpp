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

template<int I, int J>
struct Mult
{
  enum { value = I + Mult<I,J-1>::value };
};

template<int I>
struct Mult<I,0>
{
  enum { value = 0 };
};

template<int I>
struct Mult<0,I>
{
  enum { value = 0 };
};

template<int I>
struct Mult<I,1>
{
  enum { value = I };
};

template<int I>
struct Mult<1,I>
{
  enum { value = I };
};

int main() {
  assert(true);

  assert(Zero::value == 0);

  assert(Succ<Zero>::value == 1);

  assert(Factorial<0>::value == 1);

  assert(Factorial<3>::value == 6);

  assert((Mult<3,0>::value == 0));

  assert((Mult<0,1>::value == 0));

  assert((Mult<3,1>::value == 3));

  std::cout << "SUCCESS!" << std::endl;
}
