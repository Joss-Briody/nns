#include <iostream>
#include <vector>

#ifndef _ITERATOR_H
#define _ITERATOR_H

namespace iterator {

template <typename Record, typename Container>
class Iterator {
 public:
  Container& container;
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

template <typename Record, typename Container>
class BatchIterator {
    Container& container;
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
     std::vector<Record> operator*() const { return container[counter]; }

     bool operator!=(const BatchIterator &o) { return counter != o.counter; }
};

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


template <typename Record, typename Container>
class BatchIterable {
  Container& container;
  BatchIterator<Record, Container> beginIt; 
  size_t end_n;

 public:
  constexpr BatchIterable(Container&, size_t, size_t);
  BatchIterator<Record, Container> begin() const;
  BatchIterator<Record, Container> end() const;
};
}

#include "src/data/iterator.tpp"
#endif