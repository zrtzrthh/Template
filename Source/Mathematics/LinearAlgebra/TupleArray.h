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
class TupleArray<Type, 0> //模板特化
{
  template<typename, std::size_t>
  friend class TupleArray;

  template<typename, typename... Types>
  struct BaseTypeTuple:
    BaseTypeTuple<Types...>
  {
    using NextBaseType = BaseTypeTuple<Type, Type, Types...>;

    Type element;

    BaseTypeTuple() = default;

    constexpr
    BaseTypeTuple(Type element, Types ...elements):
      BaseTypeTuple<Types...>{ elements... }, //基类的构造函数处理elements
      element                { element }
    {}

    constexpr Type &
    operator[](std::size_t index)
    {
      return index ? BaseTypeTuple<Types...>::operator[](index - 1) : element;
    }

    constexpr const Type &
    operator[](std::size_t index) const
    {
      return index ? BaseTypeTuple<Types...>::operator[](index - 1) : element;
    } 
  };

  template<typename Type0>
  struct BaseTypeTuple<Type0>
  {
    using NextBaseType = BaseTypeTuple<Type, Type>;

    Type element;

    BaseTypeTuple() = default;

    constexpr
    BaseTypeTuple(Type element):
      element{ element }
    {};

    constexpr Type &
    operator[](std::size_t index)
    {
      return element;
    }

    constexpr const Type &
    operator[](std::size_t index) const
    {
      return element;
    }
  };

  template<typename... Types>
  struct BaseTypeArray
  {
    using NextBaseType = BaseTypeArray<Type, Types...>;

    Type elements[sizeof...(Types)];

    BaseTypeArray() = default;

    constexpr
    BaseTypeArray(Types... elements):
      elements{ elements... }
    {}

    template<typename BaseType>
    constexpr
    BaseTypeArray(const BaseType &baseType):
      BaseTypeArray<Types...>{ baseType, std::make_index_sequence<sizeof...(Types)>{} }
    {}

    template<typename BaseType, std::size_t... INDEXES>
    constexpr
    BaseTypeArray(const BaseType &baseType,
                  std::index_sequence<INDEXES...>):
      elements{ static_cast<Type>(baseType[INDEXES])... }
    {}

    constexpr Type &
    operator[](std::size_t index)
    {
      return elements[index];
    }

    constexpr const Type &
    operator[](std::size_t index) const
    {
      return elements[index];
    }
  };

  using NextBaseType = std::conditional_t<std::is_reference_v<Type>,
                                          BaseTypeTuple      <Type>,
                                          BaseTypeArray      <Type>>;

};

template<typename...Types>
TupleArray(Types... types) -> TupleArray<std::common_type_t<Types...>, sizeof...(Types)>;

namespace std
{
  template<typename Type, size_t LENGTH>
  struct tuple_size<::TupleArray<Type, LENGTH>>:
    integral_constant<size_t, LENGTH>
  {};

  template<typename Type, size_t LENGTH, size_t INDEX>
  struct tuple_element<INDEX, ::TupleArray<Type, LENGTH>>:
    type_identity<Type>
  {};
}

  
  
