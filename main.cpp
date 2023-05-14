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

int main() {
  assert(true);

  assert(Zero::value == 0);

  assert(Succ<Zero>::value == 1);

  std::cout << "SUCCESS!" << std::endl;
}
