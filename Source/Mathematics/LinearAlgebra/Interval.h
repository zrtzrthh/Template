#include <TupleArray.h>

#include <algorithm>

template<typename Field>
class Interval:
  public TupleArray<Field, 2> {
public:
  using TupleArray<Field, 2>::TupleArray;
  using TupleArray<Field, 2>::at;

  constexpr Interval()
  {
    clear();
  }

  constexpr void
    clear()
  {
    at(0) = 1;
    at(1) = 0;
  }

  constexpr bool
    empty() const
  {
    return at(1) < at(0);
  }

  constexpr bool
    contains(Field value,
             Field tolerance = 0) const
  {
    return at(0) - tolerance <= value &&
      at(1) + tolerance >= value;
  }

  constexpr bool
    contains(const Intervel<Field> &interval,
               Field tolerance = 0) const
  {
    return at(0) - tolerance <= interval.at(0) &&
      at(1) + tolerance >= interval.at(1);
  }
};
