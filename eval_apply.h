#include "env.h"
#include "let_list.h"

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

template<typename NameList, typename Body>
struct LLambda { };

template<typename Lambda, typename Env>
struct Closure { };

template<typename Lambda, typename Arg>
struct Call { };

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

template<typename NameList, typename Body, typename Env>
struct Eval<LLambda<NameList, Body>, Env>
{
  Closure<LLambda<NameList, Body>, Env> typedef result;
};

template<int Name, typename Body, typename Env, typename Arg>
struct Apply<Closure<Lambda<Name,Body>, Env>, Arg>
{
  typename Eval<Body, typename Let<LetSet<Name, Arg>, Env>::result>::result typedef result;
};

template<typename NameList, typename Body, typename Env, typename ValList>
struct Apply<Closure<LLambda<NameList,Body>, Env>, ValList>
{
  typename Eval<Body, typename LetList<typename NameList::result, ValList, Env>::result>::result typedef result;
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

template<typename NameList, typename Body, typename ValList, typename Env>
struct Eval<Call<LLambda<NameList, Body>, ValList>, Env>
{
  typename Apply<typename Eval<LLambda<NameList, Body>, Env>::result,
                 typename EvList<typename ValList::result, Env>::result>::result typedef result;
};
