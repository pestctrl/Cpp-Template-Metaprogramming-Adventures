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
  typedef Error result;
};

template<int Name, typename Value, typename Env>
struct Lookup<Name, Binding<Name, Value, Env>>
{
  typedef Value result;
};

template<int Name1, int Name2, typename Value, typename Env>
struct Lookup<Name1, Binding<Name2, Value, Env>>
{
  typedef typename Lookup<Name1, Env>::result result;
};

template<typename...>
struct Let { };

template<typename Env>
struct Let<Env>
{
  typedef Env result;
};

template<int Name, typename Val>
struct Let<LetSet<Name, Val>>
{
  typedef Binding<Name,Val,EmptyEnv> result;
};

template<int Name, typename Val, typename... Ts>
struct Let<LetSet<Name, Val>, Ts...>
{
  typedef Binding<Name,Val,typename Let<Ts...>::result> result;
};

#endif
