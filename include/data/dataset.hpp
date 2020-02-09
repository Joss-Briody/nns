#include <iostream>

#ifndef _DATASET_H
#define _DATASET_H

namespace data {

    template <typename Record, typename Container>
    class Dataset {
        Container records;
        public:
            Dataset(Container& records_): records(records_) {}
            
            size_t size() {
                return records.size();
            }
            
            Record& operator[](const unsigned int &i) {
                return records.at(i);
            }
    };


} // namespace data

#endif