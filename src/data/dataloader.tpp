#include <iostream>

#include "include/data/dataloader.hpp"

namespace dataloader {

    template <typename Dataset, typename Record>
    constexpr _DataIterator<Dataset, Record> _dataIteratorAt(Dataset& data, size_t n)
    {
        _DataIterator<Dataset, Record> it(data);
        for(size_t i = 0; i < n; ++i) {
            ++it;
        }
        return it;
    }

    template <typename Dataset, typename Record>
    constexpr DataLoader<Dataset, Record>::DataLoader(Dataset &data_, size_t begin_, size_t end_)
        : begin_it{_dataIteratorAt<Dataset, Record>(data_, begin_)}, end_n{end_}, dataset{data_}
    {}

    template <typename Dataset, typename Record>
    _DataIterator<Dataset, Record> DataLoader<Dataset, Record>::begin() const { 
        return begin_it; 
    }

    template <typename Dataset, typename Record>
    _DataIterator<Dataset, Record> DataLoader<Dataset, Record>::end() const { 
        return _DataIterator<Dataset, Record>{dataset, end_n}; 
    }
}