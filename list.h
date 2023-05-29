#include <climits>

#ifndef LIST_H
#define LIST_H

// Values
template<typename I, typename J>
struct Cons { };

#define NIL INT_MIN + 1

struct Nil
{
  enum { value = INT_MIN + 1 };
};

// Functions
template<typename I>
struct Car { };

template<typename I, typename J>
struct Car<Cons<I,J>>
{
  typedef I result;
};

template <typename I>
struct Cdr { };

template <typename I, typename J>
struct Cdr<Cons<I,J>>
{
  typedef J result;
};

template<typename... Ts>
struct List { };

template <>
struct List<>
{
  typedef Nil result;
};

template <typename T>
struct List<T>
{
  typedef Cons<T, Nil> result;
};

template <typename T, typename... Ts>
struct List<T, Ts...>
{
  typedef Cons<T,typename List<Ts...>::result> result;
};

void list_asserts();
#endif
