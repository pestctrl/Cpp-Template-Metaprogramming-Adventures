#include <iostream>
#include <cassert>
#include <climits>
#include "math.h"
#include "list.h"
#include "helpers.h"
#include "functional.h"
using namespace std;

// Environment MetaValues
struct Error
{
  enum { value = INT_MIN };
};

struct EmptyEnv {};

template<int Name, typename Value, typename Env>
struct Binding {};

template<int Name, typename Value>
struct LetSet { };

// Environment MetaFunctions
template<int Name, typename Env>
struct Lookup {};

template<int Name>
struct Lookup<Name, EmptyEnv>
{
  Error typedef result;
};

template<int Name, typename Value, typename Env>
struct Lookup<Name, Binding<Name, Value, Env>>
{
  Value typedef result;
};

template<int Name1, int Name2, typename Value, typename Env>
struct Lookup<Name1, Binding<Name2, Value, Env>>
{
  typename Lookup<Name1, Env>::result typedef result;
};

template<typename...>
struct Let { };

template<int Name, typename Val>
struct Let<LetSet<Name, Val>>
{
  Binding<Name,Val,EmptyEnv> typedef result;
};

template<int Name, typename Val, typename Env>
struct Let<Binding<Name, Val, Env>>
{
  Binding<Name,Val,Env> typedef result;
};

template<int Name, typename Val, typename... Ts>
struct Let<LetSet<Name, Val>, Ts...>
{
  Binding<Name,Val,typename Let<Ts...>::result> typedef result;
};

// Evaluator MetaValues
template<int name>
struct Ref { };

// Evaluator MetaFunctions
template<typename Expr, typename Env>
struct Eval { };

template<typename Closure, typename Arg>
struct Apply { };

template<int Name, typename Env>
struct Eval<Ref<Name>, Env>
{
  typename Lookup<Name, Env>::result typedef result;
};

template<typename Value, typename Env>
struct Eval<Succ<Value>, Env>
{
  Succ<Value> typedef result;
};

enum { X, Y, Z };

int main() {
  assert(true);

  math_asserts();

  list_asserts();

  functional_asserts();

  assert((Add<Num<3>::result, Num<2>::result>::result::value == 5));

  assert((Mult<Num<3>::result, Num<2>::result>::result::value == 6));

  assert((Lookup<X, Binding<X, Num<1>::result, EmptyEnv>>::result::value == 1));

  assert((Lookup<X, EmptyEnv>::result::value == INT_MIN));

  assert(Num<3>::result::value == 3);

  Let<LetSet<X,Num<1>::result>,
      LetSet<Y,Num<2>::result>,
      LetSet<Z,Num<3>::result>>::result typedef env1;

  assert((Lookup<X, env1>::result::value == 1));
  assert((Lookup<Y, env1>::result::value == 2));
  assert((Lookup<Z, env1>::result::value == 3));

  Let<LetSet<X,Num<11>::result>,
      LetSet<Y,Num<12>::result>,
      env1>::result typedef env2;

  assert((Lookup<X, env2>::result::value == 11));
  assert((Lookup<Y, env2>::result::value == 12));
  assert((Lookup<Z, env2>::result::value == 3));

  assert((Eval<Ref<X>, env2>::result::value == 11));
  assert((Eval<Ref<Y>, env2>::result::value == 12));
  assert((Eval<Ref<Z>, env2>::result::value == 3));

  assert((Eval<Num<2>::result, EmptyEnv>::result::value == 2));

  std::cout << "SUCCESS!" << std::endl;
}
