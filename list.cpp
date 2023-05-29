#include "list.h"
#include "helpers.h"
#include <cassert>

void list_asserts()
{
  typedef
    Cons<Num<3>::result,
         Num<2>::result>
    cons1;

  assert((Car<cons1>::result::value == 3));
  assert((Cdr<cons1>::result::value == 2));

  typedef
    Cons<Num<4>::result,
         Cons<Num<3>::result,
              Num<2>::result>>
    cons2;

  assert(Car<cons2>::result::value == 4);
  assert(Car<Cdr<cons2>::result>::result::value == 3);
  assert(Cdr<Cdr<cons2>::result>::result::value == 2);

  typedef List<> list1;

  assert(list1::result::value == NIL);

  typedef List<Num<4>::result>::result list2;

  assert(Car<list2>::result::value == 4);
  assert(Cdr<list2>::result::value == NIL);

  typedef
    List<Num<4>::result,
         Num<3>::result,
         Num<2>::result>::result
    list3;

  assert(Car<list3>::result::value == 4);
  assert(Car<Cdr<list3>::result>::result::value == 3);
  assert(Car<Cdr<Cdr<list3>::result>::result>::result::value == 2);
  assert(Cdr<Cdr<Cdr<list3>::result>::result>::result::value == NIL);
}
