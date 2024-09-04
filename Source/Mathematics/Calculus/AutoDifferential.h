#pragma once
//#include <iostream>
//#include <tuple>
//#include <cmath>
//
//template <typename... Args>
//struct AutoDiff {
//    std::tuple<Args...> values;
//    std::tuple<Args...> derivatives;
//
//    AutoDiff(Args... args) : values(args...), derivatives(0.0...) {}
//
//    template <std::size_t I>
//    void setDerivative(double value) {
//        std::get<I>(derivatives) = value;
//    }
//
//    template <std::size_t I>
//    double getValue() const {
//        return std::get<I>(values);
//    }
//
//    template <std::size_t I>
//    double getDerivative() const {
//        return std::get<I>(derivatives);
//    }
//
//    AutoDiff<Args...> operator+(const AutoDiff<Args...>& other) const {
//        return addOrSubtract<true>(other);
//    }
//
//    AutoDiff<Args...> operator-(const AutoDiff<Args...>& other) const {
//        return addOrSubtract<false>(other);
//    }
//
//    AutoDiff<Args...> operator*(const AutoDiff<Args...>& other) const {
//        AutoDiff<Args...> result = *this;
//        multiplyOrDivide<true>(result, other);
//        return result;
//    }
//
//    AutoDiff<Args...> operator/(const AutoDiff<Args...>& other) const {
//        AutoDiff<Args...> result = *this;
//        multiplyOrDivide<false>(result, other);
//        return result;
//    }
//
//private:
//    template <bool IsAdd>
//    AutoDiff<Args...> addOrSubtract(const AutoDiff<Args...>& other) const {
//        AutoDiff<Args...> result = *this;
//        addOrSubtractHelper<IsAdd, 0, Args...>(result, other);
//        return result;
//    }
//
//    template <bool IsMultiply>
//    void multiplyOrDivide(AutoDiff<Args...>& result, const AutoDiff<Args...>& other) const {
//        multiplyOrDivideHelper<IsMultiply, 0, Args...>(result, other);
//    }
//
//    template <bool IsAdd, std::size_t I, typename T, typename... Rest>
//    void addOrSubtractHelper(AutoDiff<Args...>& result, const AutoDiff<Args...>& other) const {
//        std::get<I>(result.values) = IsAdd ? std::get<I>(values) + std::get<I>(other.values)
//            : std::get<I>(values) - std::get<I>(other.values);
//        std::get<I>(result.derivatives) = IsAdd ? std::get<I>(derivatives) + std::get<I>(other.derivatives)
//            : std::get<I>(derivatives) - std::get<I>(other.derivatives);
//        addOrSubtractHelper<IsAdd, I + 1, Rest...>(result, other);
//    }
//
//    template <bool IsMultiply, std::size_t I, typename T, typename... Rest>
//    void multiplyOrDivideHelper(AutoDiff<Args...>& result, const AutoDiff<Args...>& other) const {
//        double value = std::get<I>(values);
//        double otherValue = std::get<I>(other.values);
//        if (IsMultiply) {
//            std::get<I>(result.values) = value * otherValue;
//            std::get<I>(result.derivatives) = std::get<I>(derivatives) * otherValue + value * std::get<I>(other.derivatives);
//        }
//        else {
//            std::get<I>(result.values) = value / otherValue;
//            std::get<I>(result.derivatives) = (std::get<I>(derivatives) * otherValue - value * std::get<I>(other.derivatives)) / (otherValue * otherValue);
//        }
//        multiplyOrDivideHelper<IsMultiply, I + 1, Rest...>(result, other);
//    }
//
//    template <bool IsAdd, std::size_t I>
//    void addOrSubtractHelper(AutoDiff<Args...>& result, const AutoDiff<Args...>& other) const {}
//
//    template <bool IsMultiply, std::size_t I>
//    void multiplyOrDivideHelper(AutoDiff<Args...>& result, const AutoDiff<Args...>& other) const {}
//};

#include <iostream>

void
print();