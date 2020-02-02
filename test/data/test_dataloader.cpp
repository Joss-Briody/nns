#define CATCH_CONFIG_MAIN

#include <utility>
#include <vector>

#include "include/tests/catch.hpp"
#include "include/data/dataloader.hpp"
#include "include/data/dataset.hpp"

TEST_CASE("DataLoader can be iterated", "[dataloader]") {
    typedef std::vector<float> x_type;
    typedef std::pair<x_type, unsigned int> Record;
    typedef data::Dataset<Record, std::vector<Record>> DatasetType;
    std::vector<Record> data = {
        std::make_pair<x_type, int>({1.0, 2.0, 3.0}, 1),
        std::make_pair<x_type, int>({4.0, 5.0, 6.0}, 0)
    };
    DatasetType dataset(data);
    dataloader::DataLoader<DatasetType, Record> dataLoader(dataset, 0, 2);

    std::vector<Record> res;
    for(auto& i : dataLoader) {
        res.push_back(i);
    }
    REQUIRE(res[0] == data[0]);
    REQUIRE(res[1] == data[1]);
}
