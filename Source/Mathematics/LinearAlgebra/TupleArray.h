#pragma once

#include <type_traits>

#include <cassert>
#include <utility>

template<typename Type, std::size_t LENGTH>
class TupleArray:
  private TupleArray<Type, LENGTH-1>::NextBaseType
{
  template<typename, std::size_t>
  friend class TupleArray;

  using BaseType = typename TupleArray<Type, LENGTH-1>::NextBaseType;
  using NextBaseType = typename BaseType::NextBaseType;

public:
  using BaseType::BaseType;
  using BaseType::operator[];

  constexpr Type &
  at(std::size_t index)
  {
    assert(0 <= index && index < LENGTH);
    return operator[](index);
  }
  constexpr const Type &
    at(std::size_t index) const
  {
    assert(0 <= index && index < LENGTH);
    return operator[](index);
  }
};

template<typename Type>
class TupleArray<Type, 0>
{
  template<typename, std::size_t>
  friend class TupleArray;

  template<typename, typename... Types>
  struct BaseTypeTuple:
    BaseTypeTuple<Types...>
  {
    using NextBaseType = BaseTypeTuple<Type, Type, Types...>;

    Type elenent;

    BaseTypeTuple() = default;

    constexpr
    BaseTypeTuple(Type elenent, Types ...elements):
      BaseTypeTuple<Types...>{ elements... }
      element                { element }
      {}
  };

};

  
  
