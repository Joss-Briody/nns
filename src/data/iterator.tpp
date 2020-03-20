#include <iostream>

#include "include/data/iterator.hpp"

namespace iterator {

template <typename Record, typename Container>
constexpr typename Iterable<Record, Container>::Iterator iteratorAt(
    Container& container, size_t n) {
  typename Iterable<Record, Container>::Iterator it(container);
  for (size_t i = 0; i < n; ++i) {
    ++it;
  }
  return it;
}

template <typename Record, typename Container, typename Batch>
constexpr typename BatchIterable<Record, Container, Batch>::BatchIterator
batchIteratorAt(Container& container, size_t n) {
  typename BatchIterable<Record, Container, Batch>::BatchIterator it(container);
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

template <typename Record, typename Container, typename Batch>
constexpr BatchIterable<Record, Container, Batch>::BatchIterable(
    Container& container_, size_t begin_, size_t end_)
    : beginIt{batchIteratorAt<Record, Container, Batch>(container_, begin_)},
      end_n{end_},
      container{container_} {}

template <typename Record, typename Container>
typename Iterable<Record, Container>::Iterator
Iterable<Record, Container>::begin() const {
  return beginIt;
}
template <typename Record, typename Container, typename Batch>
typename BatchIterable<Record, Container, Batch>::BatchIterator
BatchIterable<Record, Container, Batch>::begin() const {
  return beginIt;
}

template <typename Record, typename Container>
typename Iterable<Record, Container>::Iterator
Iterable<Record, Container>::end() const {
  return typename Iterable<Record, Container>::Iterator{container, end_n};
}

template <typename Record, typename Container, typename Batch>
typename BatchIterable<Record, Container, Batch>::BatchIterator
BatchIterable<Record, Container, Batch>::end() const {
  return typename BatchIterable<Record, Container, Batch>::BatchIterator{
      container, end_n};
}
}