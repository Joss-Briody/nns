#include <utility>
#include <vector>

#include "include/tests/catch.hpp"
#include "include/data/dataset.hpp"

TEST_CASE("Dataset can be indexed", "[dataset]") {
    typedef std::vector<float> x_type;
    typedef std::pair<x_type, unsigned int> Record;
    std::vector<Record> data = {
        std::make_pair<x_type, int>({1.0, 2.0, 3.0}, 1),
        std::make_pair<x_type, int>({4.0, 5.0, 6.0}, 0)
    };
    data::Dataset<Record, std::vector<Record>> dataset(data);
    REQUIRE(dataset[0] == data[0]);
    REQUIRE(dataset[1] == data[1]);
    }
