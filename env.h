#ifndef ENV_H
#define ENV_H

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

#endif
