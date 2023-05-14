#include "list.h"
#include "helpers.h"
#include <cassert>

void list_asserts()
{
  Cons<GenNumber<3>::result,
       GenNumber<2>::result> typedef cons;
  assert((Car<cons>::result::value == 3));
  assert((Cdr<cons>::result::value == 2));
}
