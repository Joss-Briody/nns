#include <iostream>

#include "include/data/iterator.hpp"

namespace iterator {

template <typename Record, typename Container>
constexpr Iterator<Record, Container> iteratorAt(Container& container,
                                                 size_t n) {
  Iterator<Record, Container> it(container);
  for (size_t i = 0; i < n; ++i) {
    ++it;
  }
  return it;
}
template <typename Record, typename Container>
constexpr Iterable<Record, Container>::Iterable(Container& container_,
                                                size_t begin_, size_t end_)
    : beginIt{iteratorAt<Record, Container>(container_, begin_)},
      end_n{end_},
      container{container_} {}

template <typename Record, typename Container>
Iterator<Record, Container> Iterable<Record, Container>::begin() const {
  return beginIt;
}
template <typename Record, typename Container>
Iterator<Record, Container> Iterable<Record, Container>::end() const {
  return Iterator<Record, Container>{container, end_n};
}
}