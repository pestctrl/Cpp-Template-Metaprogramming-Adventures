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

template<typename Env>
struct Let<Env>
{
  Env typedef result;
};

template<int Name, typename Val>
struct Let<LetSet<Name, Val>>
{
  Binding<Name,Val,EmptyEnv> typedef result;
};

template<int Name, typename Val, typename... Ts>
struct Let<LetSet<Name, Val>, Ts...>
{
  Binding<Name,Val,typename Let<Ts...>::result> typedef result;
};

// Evaluator MetaValues
template<int name>
struct Ref { };

template<int name>
struct Atom { };

template<int A>
struct ENum
{ };

template<typename A, typename B>
struct EAdd { };

template<typename A, typename B>
struct EMult { };

template<int Arg, typename Body>
struct Lambda { };

template<typename Lambda, typename Env>
struct Closure { };

template<typename Lambda, typename Arg>
struct Call { };

template<int Name, typename Rest>
struct NameCons
{ };

template<int... Names>
struct NameList
{ };

template<int Name>
struct NameList<Name>
{
  NameCons<Name, Nil> typedef result;
};

template<int Name, int... Names>
struct NameList<Name, Names...>
{
  NameCons<Name, typename NameList<Names...>::result> typedef result;
};

template<typename Val, typename Rest>
struct ValCons
{ };

template<typename... Vals>
struct ValList
{ };

template<typename Val>
struct ValList<Val>
{
  ValCons<Val, Nil> typedef result;
};

template<typename Val, typename... Vals>
struct ValList<Val, Vals...>
{
  ValCons<Val, typename ValList<Vals...>::result> typedef result;
};

template<typename Names, typename Vals, typename Env>
struct LetList
{

};

template<int Name, typename Val, typename Env>
struct LetList<NameCons<Name, Nil>, ValCons<Val, Nil>, Env>
{
  Binding<Name,Val,Env> typedef result;
};

template<int Name, typename Names, typename Val, typename Vals, typename Env>
struct LetList<NameCons<Name, Names>, ValCons<Val, Vals>, Env>
{
  Binding<Name,Val,typename LetList<Names, Vals, Env>::result> typedef result;
};

// Evaluator MetaFunctions
template<typename Expr, typename Env>
struct Eval { };

template<typename ExprList, typename Env>
struct EvList { };

template<typename Closure, typename Arg>
struct Apply { };

template<int Name, typename Env>
struct Eval<Ref<Name>, Env>
{
  typename Lookup<Name, Env>::result typedef result;
};

template<int Name, typename Env>
struct Eval<Atom<Name>, Env>
{
  typename Num<Name>::result typedef result;
};

template<typename Value, typename Env>
struct Eval<Succ<Value>, Env>
{
  Succ<Value> typedef result;
};

template<int Value, typename Env>
struct Eval<ENum<Value>, Env>
{
  typename Num<Value>::result typedef result;
};

template<typename A, typename B, typename Env>
struct Eval<EAdd<A,B>, Env>
{
  typename Add<typename Eval<A,Env>::result,typename Eval<B,Env>::result>::result typedef result;
};

template<typename A, typename B, typename Env>
struct Eval<EMult<A,B>, Env>
{
  typename Mult<typename Eval<A,Env>::result,typename Eval<B,Env>::result>::result typedef result;
};

template<int Name, typename Body, typename Env>
struct Eval<Lambda<Name, Body>, Env>
{
  Closure<Lambda<Name, Body>, Env> typedef result;
};

template<int Name, typename Body, typename Env, typename Arg>
struct Apply<Closure<Lambda<Name,Body>, Env>, Arg>
{
  typename Eval<Body, typename Let<LetSet<Name, Arg>, Env>::result>::result typedef result;
};

template<int Name, typename Body, typename Arg, typename Env>
struct Eval<Call<Lambda<Name, Body>, Arg>, Env>
{
  typename Apply<typename Eval<Lambda<Name, Body>, Env>::result,
                 typename Eval<Arg, Env>::result>::result typedef result;
};

template<typename Val, typename Env>
struct EvList<ValCons<Val,Nil>, Env>
{
  ValCons<typename Eval<Val, Env>::result, Nil> typedef result;
};

template<typename Val, typename Vals, typename Env>
struct EvList<ValCons<Val,Vals>, Env>
{
  ValCons<typename Eval<Val, Env>::result,
          typename EvList<Vals,Env>::result> typedef result;
};

enum {
    A, B, C, D, E, F, G,
    H, I, J, K, L, M, N, O, P,
    Q, R, S, T, U, V,
    W, X, Y, Z
};

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

  assert((Eval<Atom<X>, env2>::result::value == 23));
  assert((Eval<Atom<Y>, env2>::result::value == 24));
  assert((Eval<Atom<Z>, env2>::result::value == 25));

  assert((Eval<Num<2>::result, EmptyEnv>::result::value == 2));

  assert((Eval<ENum<2>, EmptyEnv>::result::value == 2));

  assert((Eval<EAdd<ENum<2>, ENum<3>>, EmptyEnv>::result::value == 5));

  assert((Eval<Call<Lambda<X, Ref<X>>, ENum<2>>, EmptyEnv>::result::value == 2));

  assert((Eval<Call<Lambda<X, EAdd<ENum<1>, Ref<X>>>, Num<2>::result>, EmptyEnv>::result::value == 3));

  assert((Eval<Call<Lambda<X, EAdd<ENum<5>, Ref<X>>>, Num<2>::result>, EmptyEnv>::result::value == 7));

  assert((Eval<Call<Lambda<X, EMult<ENum<5>, Ref<X>>>, Num<2>::result>, EmptyEnv>::result::value == 10));

  assert((Eval<Call<Lambda<X, EMult<ENum<5>, Ref<X>>>, EMult<ENum<4>, ENum<3>>>, EmptyEnv>::result::value == 60));

  // Next step: rework lambda to have multiple arguments
  LetList<NameList<X,Y,Z>::result,
          ValList<Num<1>::result,
                  Num<2>::result,
                  Num<3>::result>::result,
          EmptyEnv>::result typedef env3;

  assert((Eval<Ref<X>, env3>::result::value == 1));
  assert((Eval<Ref<Y>, env3>::result::value == 2));
  assert((Eval<Ref<Z>, env3>::result::value == 3));

  LetList<NameList<X,Y>::result,
          EvList<ValList<EAdd<ENum<1>, ENum<2>>,
                         EMult<ENum<2>, ENum<3>>>::result,
                 EmptyEnv>::result,
          EmptyEnv>::result typedef env4;

  assert((Eval<Ref<X>, env4>::result::value == 3));
  assert((Eval<Ref<Y>, env4>::result::value == 6));

  std::cout << "SUCCESS!" << std::endl;
}
