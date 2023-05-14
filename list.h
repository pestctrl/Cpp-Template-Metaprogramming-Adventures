// Values
template<typename I, typename J>
struct Cons { };

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

void list_asserts();
