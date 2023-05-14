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

int main() {
  assert(true);

  assert(Zero::value == 0);

  assert(Succ<Zero>::value == 1);

  assert(Factorial<0>::value == 1);

  assert(Factorial<3>::value == 6);

  std::cout << "SUCCESS!" << std::endl;
}
