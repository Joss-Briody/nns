#include <iostream>
#include <vector>

#ifndef _ITERATOR_H
#define _ITERATOR_H

namespace iterator {

template <typename Record, typename Container>
class Iterable {
 public:
  class Iterator {
   public:
    Container &container;
    size_t counter{0};
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
  constexpr Iterable(Container &, size_t, size_t);
  Iterable<Record, Container>::Iterator begin() const;
  Iterable<Record, Container>::Iterator end() const;

 private:
  Container &container;
  Iterable<Record, Container>::Iterator beginIt;
  size_t end_n;
};

template <typename Record, typename Container, typename Batch>
class BatchIterable {
 public:
  class BatchIterator {
    Container &container;
    size_t counter{0};

   public:
    constexpr BatchIterator() = default;
    constexpr BatchIterator(Container &container_)
        : container(container_), counter(0) {}
    constexpr BatchIterator(Container &container_, size_t i)
        : container(container_), counter(i) {}

    constexpr BatchIterator &operator++() {
      counter++;
      return *this;
    }

    // return a container by value because its a new batch
    Batch operator*() const { return container[counter]; }

    bool operator!=(const BatchIterator &o) { return counter != o.counter; }
  };
  constexpr BatchIterable(Container&, size_t, size_t);
  BatchIterable<Record, Container, Batch>::BatchIterator begin() const;
  BatchIterable<Record, Container, Batch>::BatchIterator end() const;

 private:
  Container &container;
  BatchIterable<Record, Container, Batch>::BatchIterator beginIt;
  size_t end_n;
};
}

#include "src/data/iterator.tpp"
#endif