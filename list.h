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
  I typedef result;
};

template <typename I>
struct Cdr { };

template <typename I, typename J>
struct Cdr<Cons<I,J>>
{
  J typedef result;
};

template<typename... Ts>
struct List { };

template <>
struct List<>
{
  Nil typedef result;
};

template <typename T>
struct List<T>
{
  Cons<T, Nil> typedef result;
};

template <typename T, typename... Ts>
struct List<T, Ts...>
{
  Cons<T,typename List<Ts...>::result> typedef result;
};

void list_asserts();
#endif
