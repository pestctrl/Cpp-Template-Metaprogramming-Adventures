#include <iostream>
#include <cassert>
#include <climits>
#include "math.h"
#include "list.h"
#include "helpers.h"
#include "functional.h"
#include "env.h"
#include "eval_apply.h"
using namespace std;

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

  typedef
    Let<LetSet<X,Num<1>::result>,
        LetSet<Y,Num<2>::result>,
        LetSet<Z,Num<3>::result>>::result
    env1;

  assert((Lookup<X, env1>::result::value == 1));
  assert((Lookup<Y, env1>::result::value == 2));
  assert((Lookup<Z, env1>::result::value == 3));

  typedef
    Let<LetSet<X,Num<11>::result>,
        LetSet<Y,Num<12>::result>,
        env1>::result
    env2;

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

  assert((Eval<Call<Lambda<X, EAdd<ENum<1>, Ref<X>>>, ENum<2>>, EmptyEnv>::result::value == 3));

  assert((Eval<Call<Lambda<X, EAdd<ENum<5>, Ref<X>>>, ENum<2>>, EmptyEnv>::result::value == 7));

  assert((Eval<Call<Lambda<X, EMult<ENum<5>, Ref<X>>>, ENum<2>>, EmptyEnv>::result::value == 10));

  assert((Eval<Call<Lambda<X, EMult<ENum<5>, Ref<X>>>, EMult<ENum<4>, ENum<3>>>, EmptyEnv>::result::value == 60));

  // Next step: rework lambda to have multiple arguments
  typedef
    LetList<NameList<X,Y,Z>::result,
            ValList<Num<1>::result,
                    Num<2>::result,
                    Num<3>::result>::result,
            EmptyEnv>::result
    env3;

  assert((Eval<Ref<X>, env3>::result::value == 1));
  assert((Eval<Ref<Y>, env3>::result::value == 2));
  assert((Eval<Ref<Z>, env3>::result::value == 3));

  typedef
    LetList<NameList<X,Y>::result,
            EvList<ValList<EAdd<ENum<1>, ENum<2>>,
                           EMult<ENum<2>, ENum<3>>>::result,
                   EmptyEnv>::result,
            EmptyEnv>::result
    env4;

  assert((Eval<Ref<X>, env4>::result::value == 3));
  assert((Eval<Ref<Y>, env4>::result::value == 6));

  assert((Eval<Call<LLambda<NameList<X>, EMult<ENum<5>, Ref<X>>>, ValList<ENum<2>>>, EmptyEnv>::result::value == 10));

  typedef
    LLambda<NameList<X>, EMult<Ref<X>, Ref<X>>>
    square;

  assert((Eval<Call<square, ValList<ENum<2>>>, EmptyEnv>::result::value == 4));

  typedef
    LLambda<NameList<X, Y>, EAdd<Call<square, ValList<Ref<X>>>,
                                 Call<square, ValList<Ref<Y>>>>>
    sos;

  assert((Eval<Call<sos, ValList<ENum<3>,ENum<4>>>, EmptyEnv>::result::value == 25));

  std::cout << "SUCCESS!" << std::endl;
}
