#include <iostream>
#include <cassert>
using namespace std;

struct Zero
{
  enum { value = 0 };
};

int main() {
  assert(true);

  assert(Zero::value == 0);

  std::cout << "SUCCESS!" << std::endl;
}
