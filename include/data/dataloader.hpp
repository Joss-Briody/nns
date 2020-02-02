#include <iostream>

#ifndef _DATALOADER_H
#define _DATALOADER_H

namespace dataloader  {

    template <typename Dataset, typename Record>
    class _DataIterator {
        Dataset &data;
        size_t counter{0};

    public:
        constexpr _DataIterator() = default;
        constexpr _DataIterator(Dataset &data_) : data(data_), counter(0) {}
        constexpr _DataIterator(Dataset &data_, size_t i) : data(data_), counter(i) {}

        constexpr _DataIterator &operator++() {
            counter++;
            return *this;
        }

        Record &operator*() const {
            return data[counter];
        }

        bool operator!=(const _DataIterator &o) {
            return counter != o.counter;
        }
    };

    template <typename Dataset, typename Record>
    class DataLoader {
        Dataset& dataset;
        _DataIterator<Dataset, Record> begin_it;
        size_t end_n;

        public:
            constexpr DataLoader(Dataset&, size_t, size_t);
            _DataIterator<Dataset, Record> begin() const;
            _DataIterator<Dataset, Record> end() const;
    };

} // namespace dataloader

#include "src/data/dataloader.tpp"
#endif