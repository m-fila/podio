#include "podio/CollectionBase.h"

#include <concepts>
#include <ranges>
#include <string_view>

namespace podio {

template <typename T>
concept Collection = !std::is_abstract_v<T> && requires {
  requires std::derived_from<T, CollectionBase>;
  requires std::ranges::input_range<T>;
  requires std::movable<T>;
  requires std::move_constructible<T>;
  { T::typeName } -> std::convertible_to<std::string_view>;
  { std::bool_constant<(T::typeName, true)>() } -> std::same_as<std::true_type>; // ~is annotated with constexpr
  { T::valueTypeName } -> std::convertible_to<std::string_view>;
  { std::bool_constant<(T::valueTypeName, true)>() } -> std::same_as<std::true_type>; // ~is annotated with constexpr
  { T::dataTypeName } -> std::convertible_to<std::string_view>;
  { std::bool_constant<(T::dataTypeName, true)>() } -> std::same_as<std::true_type>; // ~is annotated with constexpr
};

} // namespace podio