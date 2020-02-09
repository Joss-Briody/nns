#include <iostream>

#ifndef _ITERATOR_H
#define _ITERATOR_H

namespace iterator {

template <typename Record, typename Container>
class Iterator {
  Container& container;
  size_t counter{0};

 public:
  constexpr Iterator() = default;
  constexpr Iterator(Container &container_)
      : container(container_), counter(0) {}
  constexpr Iterator(Container &container_, size_t i)
      : container(container_), counter(i) {}

  constexpr Iterator &operator++() {
    counter++;
    return *this;
  }

  Record &operator*() const { return container[counter]; }

  bool operator!=(const Iterator &o) { return counter != o.counter; }
};

template <typename Record, typename Container>
class BatchIterator : public Iterator<Record, Container> {
     Container operator*() const { return container[counter]; }
}

template <typename Record, typename Container>
class Iterable {
  Container& container;
  Iterator<Record, Container> beginIt; 
  size_t end_n;

 public:
  constexpr Iterable(Container&, size_t, size_t);
  Iterator<Record, Container> begin() const;
  Iterator<Record, Container> end() const;
};
}

#include "src/data/iterator.tpp"
#endif