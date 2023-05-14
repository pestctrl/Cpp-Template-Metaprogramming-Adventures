#include "list.h"
#include "helpers.h"
#include <cassert>

void list_asserts()
{
  Cons<Num<3>::result,
       Num<2>::result> typedef cons1;

  assert((Car<cons1>::result::value == 3));
  assert((Cdr<cons1>::result::value == 2));

  Cons<Num<4>::result,
       Cons<Num<3>::result,
            Num<2>::result>> typedef cons2;

  assert(Car<cons2>::result::value == 4);
  assert(Car<Cdr<cons2>::result>::result::value == 3);
  assert(Cdr<Cdr<cons2>::result>::result::value == 2);

  List<> typedef list1;

  assert(list1::result::value == NIL);

  List<Num<4>::result>::result typedef list2;

  assert(Car<list2>::result::value == 4);
  assert(Cdr<list2>::result::value == NIL);

  List<Num<4>::result,
       Num<3>::result,
       Num<2>::result>::result typedef list3;

  assert(Car<list3>::result::value == 4);
  assert(Car<Cdr<list3>::result>::result::value == 3);
  assert(Car<Cdr<Cdr<list3>::result>::result>::result::value == 2);
  assert(Cdr<Cdr<Cdr<list3>::result>::result>::result::value == NIL);
}
