#include "list.h"
#include "helpers.h"
#include <cassert>

void list_asserts()
{
  assert((Car<Cons<GenNumber<3>::result,GenNumber<2>::result>>::result::value == 3));
  assert((Cdr<Cons<GenNumber<3>::result,GenNumber<2>::result>>::result::value == 2));
}
