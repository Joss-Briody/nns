#include <iostream>

namespace data {

    template <typename Record, typename Container>
    class Dataset {
        Container records;

        public:
            Dataset(Container& records_): records(records_) {}
            
            Record &operator[](const unsigned int &i) {
                return records.at(i);
            }
    };


} // namespace data
