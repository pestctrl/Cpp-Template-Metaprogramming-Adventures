#include "env.h"

#ifndef LET_LIST_H
#define LET_LIST_H

template<int Name, typename Rest>
struct NameCons { };

template<int... Names>
struct NameList { };

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
struct ValCons { };

template<typename... Vals>
struct ValList { };

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
#endif
