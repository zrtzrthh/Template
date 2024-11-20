#pragma once

#include <TupleArray.h>

#include <compare>

#pragma region declarations

template<typename Field, std::size_t... SHAPE>
class Tensor;

template <typename T>
struct IsScalar:
  std::true_type
{};

template <typename Field, std::size_t... SHAPE>
struct IsScalar<Tensor<Field, SHAPE...>>:
  std::false_type
{};

template <typename T>
concept Scalar = IsScalar<T>::value;

template<typename Field>
class Tensor<Field> {
public:
  template<std::size_t...>
  using RemoveIndex = Tensor<Field>;

  Tensor() = delete;
};

template<typename Field, std::size_t DIMENSION>
using Vector = Tensor<Field, DIMENSION>;

using Vector2d = Vector<double, 2>;
using Vector2f = Vector<float, 2>;
using Vector2i = Vector<int, 2>;
using Vector3d = Vector<double, 3>;
using Vector3f = Vector<float, 3>;
using Vector3i = Vector<int, 3>;
using Vector4d = Vector<double, 4>;
using Vector4f = Vector<float, 4>;
using Vector4i = Vector<int, 4>;

template<typename Field, std::size_t DIMENSION0, std::size_t DIMENSION1 = DIMENSION0>
using Matrix = Tensor<Field, DIMENSION0, DIMENSION1>;
using Matrix2d = Matrix<double, 2>;
using Matrix2f = Matrix<float, 2>;
using Matrix2i = Matrix<int, 2>;
using Matrix3d = Matrix<double, 3>;
using Matrix3f = Matrix<float, 3>;
using Matrix3i = Matrix<int, 3>;
using Matrix4d = Matrix<double, 4>;
using Matrix4f = Matrix<float, 4>;
using Matrix4i = Matrix<int, 4>;

#pragma endregion

template<typename Field, std::size_t DIMENSION, std::size_t... SHAPE>
class Tensor<Field, DIMENSION, SHAPE...>:
  public TupleArray<std::conditional_t<(sizeof...(SHAPE) > 0), Tensor<Field, SHAPE...>, Field>, DIMENSION>
{
#pragma region static
  using BaseClass = TupleArray<std::conditional_t<(sizeof...(SHAPE) > 0), Tensor<Field, SHAPE...>, Field>, DIMENSION>;

  constexpr static std::size_t RANK = 1 + sizeof...(SHAPE);
  constexpr static bool IS_VECTOR = RANK == 1;
  constexpr static bool IS_MATRIX = RANK == 2;

  template<typename, std::size_t...>
  friend class Tensor;

  // avoid sizeof...() with multiple parameter packs due to msvc compiler bug
  template<std::size_t...>
  struct IsEmpty:
    std::false_type
  {};

  template<>
  struct IsEmpty<>:
    std::true_type
  {};
#pragma endregion

public:
#pragma region constructors
  using BaseClass::BaseClass;
#pragma endregion

#pragma region accessors
  using BaseClass::operator[];
  using BaseClass::at;

public:
  template<std::size_t INDEX, std::size_t... SHAPE1>
  using RemoveIndex = std::conditional_t<!INDEX,std::conditional_t<!IsEmpty<SHAPE1..., SHAPE...>::value,Tensor<Field, SHAPE1..., SHAPE...>,Field>,
                                         typename Tensor<Field, SHAPE...>::template RemoveIndex<INDEX - 1, SHAPE1..., DIMENSION>>;

public:
  template<std::size_t INDEX>
  constexpr RemoveIndex<INDEX>
    isolateIndex(std::size_t index) const
  {
    if constexpr (!INDEX)
      return (*this)[index];
    else
    {
      RemoveIndex<INDEX> isolatedIndex;

      for (int i = 0; i < DIMENSION; i++)
      {
        isolatedIndex[i] = (*this)[i].template isolateIndex<INDEX - 1>(index);
      }
      return isolatedIndex;
    }
  }

  constexpr Tensor<Field, SHAPE...>
  row(std::size_t index) const requires (IS_MATRIX)
  {
    return (*this)[index];
  }

  constexpr Tensor<Field, DIMENSION>
  column(std::size_t index) const requires (IS_MATRIX)
  {
    return isolateIndex<1>(index);
  }

#pragma endregion

#pragma region comparison
  template<typename Field1>
  constexpr std::compare_three_way_result_t<Field, Field1>
  operator<=>(const Tensor<Field1, DIMENSION, SHAPE...> &tensor) const
  {
    for (int i = 0; i < DIMENSION; i++)
    {
      const  std::compare_three_way_result_t<Field, Field1> &compare = (*this)[i] <=> tensor[i];
      if (compare == 0 || i == DIMENSION - 1)
        return compare;
    }
  }

  template<typename Field1>
  constexpr bool
  operator==(const Tensor<Field1, DIMENSION, SHAPE...> &tensor) const
  {
    for (int i = 0; i < DIMENSION; i++)
    {
      if ((*this)[i] != tensor[i])
        return false;
    }
    return true;
  }

  template<typename Field1>
  constexpr bool
  operator!=(const Tensor<Field1, DIMENSION, SHAPE...> &tensor) const
  {
    return !((*this) == tensor);
  }

  template<typename Field1>
  constexpr bool
  operator<(const Tensor<Field1, DIMENSION, SHAPE...> &tensor) const
  {
    return ((*this) <=> tensor) < 0;
  }

  template<typename Field1>
  constexpr bool
  operator>(const Tensor<Field1, DIMENSION, SHAPE...> &tensor) const
  {
    return ((*this) <=> tensor) > 0;
  }

  template<typename Field1>
  constexpr bool
  operator<=(const Tensor<Field1, DIMENSION, SHAPE...> &tensor) const
  {
    return ((*this) <=> tensor) <= 0;
  }

  template<typename Field1>
  constexpr bool
  operator>=(const Tensor<Field1, DIMENSION, SHAPE...> &tensor) const
  {
    return ((*this) <=> tensor) >= 0;
  }

#pragma endregion

#pragma region addition and subtraction

  template<typename Field1>
  constexpr Tensor<Field, DIMENSION, SHAPE...> &
  operator+=(const Tensor<Field1, DIMENSION, SHAPE...> &tensor)
  {
    for (int i = 0; i < DIMENSION; i++)
    {
      (*this)[i] += tensor[i];
    }
    return *this;
  }

  template<typename Field1>
  constexpr Tensor<std::common_type_t<Field, Field1>, DIMENSION, SHAPE...>
  operator+(const Tensor<Field1, DIMENSION, SHAPE...> &tensor) const
  {
    return Tensor<std::common_type_t<Field, Field1>, DIMENSION, SHAPE...>(*this) += tensor;
  }

  template<typename Field1>
  constexpr Tensor<std::common_type_t<Field, Field1>, DIMENSION, SHAPE...>
  operator-(const Tensor<Field1, DIMENSION, SHAPE...> &tensor) const
  {
    return Tensor<std::common_type_t<Field, Field1>, DIMENSION, SHAPE...>(*this) -= tensor;
  }

#pragma endregion

#pragma region scalar multiplication and division

  template<Scalar Field1>
  constexpr Tensor<Field, DIMENSION, SHAPE...> &
  operator*=(Field1 scalar)
  {
    for (int i = 0; i < DIMENSION; i++)
      (*this)[i] *= scalar;
    return *this;
  }

  template<Scalar Field1>
  constexpr Tensor<Field, DIMENSION, SHAPE...> &
  operator/=(Field1 scalar)
  {
    for (int i = 0; i < DIMENSION; i++)
      (*this)[i] /= scalar;
    return *this;
  }

  template<Scalar Field1>
  constexpr Tensor<std::common_type_t<Field, Field1>, DIMENSION, SHAPE...>
  operator*(Field1 scalar) const
  {
    return Tensor<std::common_type_t<Field, Field1>, DIMENSION, SHAPE...>(*this) *= scalar;
  }

  template<Scalar Field1>
  constexpr Tensor<std::common_type_t<Field, Field1>, DIMENSION, SHAPE...>
  operator/(Field1 scalar) const
  {
    return Tensor<std::common_type_t<Field, Field1>, DIMENSION, SHAPE...>(*this) /= scalar;
  }

  constexpr Tensor<Field, DIMENSION, SHAPE...>
  operator-() const
  {
    return (*this)*-1;
  }

  template<Scalar Field1>
  friend constexpr Tensor<std::common_type_t<Field, Field1>, DIMENSION, SHAPE...>
  operator*(Field1 scalar, const Tensor<Field, DIMENSION, SHAPE...> &tensor)
  {
    return tensor * scalar;
  }

#pragma endregion

#pragma region tensor operations
  template<typename Field1, std::size_t... SHAPE1>
  constexpr Tensor<std::common_type_t<Field, Field1>, DIMENSION, SHAPE..., SHAPE1...>
  tensorProduct(const Tensor<Field1, SHAPE1...> &tensor) const
  {
    Tensor<std::common_type_t<Field, Field1>, DIMENSION, SHAPE..., SHAPE1...> product{};
    for (int i = 0; i < DIMENSION; i++)
    {
      if constexpr (IS_VECTOR)
        product[i] = (*this)[i] * tensor;
      else
        product[i] = (*this)[i].tensorProduct(tensor);
    }
    return product;
  }

  template<std::size_t INDEX0, std::size_t INDEX1>
  constexpr typename RemoveIndex<INDEX0>::template RemoveIndex<INDEX1 - 1>
  contract() const
  {
    typename RemoveIndex<INDEX0>::template RemoveIndex<INDEX1 - 1> contraction{};
    for (int i = 0; i < DIMENSION; i++)
    {
      if constexpr (!INDEX0)
        contraction += (*this)[i].template isolateIndex<INDEX1 - 1>(i);
      else
        contraction[i] = (*this)[i].template contract<INDEX0 - 1, INDEX1 - 1>();
    }
    return contraction;
  }

  template<typename Field1, std::size_t... SHAPE1>
  constexpr typename Tensor<std::common_type_t<Field, Field1>, DIMENSION, SHAPE...>::template RemoveIndex<RANK - 1>::template RemoveIndex<RANK - 1>
  operator*(const Tensor<Field1, SHAPE1...> &tensor) const
  {
    return tensorProduct(tensor).template contract<RANK - 1, RANK>();
  }
#pragma endregion

#pragma region matrix operations
  constexpr Field trace() const requires (IS_MATRIX)
  {
    return contract<0, 1>();
  }
#pragma endregion

#pragma region vector operations
  template<typename Field1>
    requires (DIMENSION == 3)
  constexpr Vector<std::common_type_t<Field, Field1>, 3>
  cross(const Vector<Field1, 3> &vector) const requires (IS_VECTOR)
  {
    return Vector<std::common_type_t<Field, Field1>, 3>{ (*this)[1]*vector[2] - (*this)[2]*vector[1],
                                                         (*this)[2]*vector[0] - (*this)[0]*vector[2],
                                                         (*this)[0]*vector[1] - (*this)[1]*vector[0] };
  }

  constexpr std::remove_cvref_t<Field>
  norm() const
  {
    std::remove_cvref_t<Field> norm2{};
    for (int i = 0; i < DIMENSION; i++)
    {
      norm2 += at(i) * at(i);
    }
    return norm2;
  }

  constexpr Vector<Field, DIMENSION - 1>
  project() const requires (IS_VECTOR)
  {
    Vector<Field, DIMENSION - 1> projection;
    for (int i = 0; i < DIMENSION - 1; i++)
    {
      projection.at(i) = at(i) / at(DIMENSION - 1);
    }
    return projection;
  }
#pragma endregion
};
