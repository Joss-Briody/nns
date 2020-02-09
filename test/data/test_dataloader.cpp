#include <utility>
#include <vector>

#include "include/tests/catch.hpp"
#include "include/data/dataloader.hpp"
#include "include/data/dataset.hpp"
#include "include/data/sampler.hpp"

TEST_CASE("DataLoader can be iterated", "[dataloader]") {
    typedef std::vector<u_int8_t> x_type;
    typedef std::pair<x_type, size_t> Record;
    typedef std::vector<Record> VectorContainer;
    typedef data::Dataset<Record, VectorContainer> VectorDataset;
    VectorContainer data = {
        std::make_pair<x_type, int>({1, 2, 3}, 1),
        std::make_pair<x_type, int>({4, 5, 6}, 0),
        std::make_pair<x_type, int>({1, 2, 3}, 1),
        std::make_pair<x_type, int>({4, 5, 6}, 0),
        std::make_pair<x_type, int>({1, 2, 3}, 1),
        std::make_pair<x_type, int>({4, 5, 6}, 0),
    };
    VectorDataset dataset(data);
    sampler::RandomSampler<Record, VectorContainer> sampler(dataset, 3);
    dataloader::VectorDataLoader dl(sampler);

    std::vector<std::vector<Record>> res;
    for(auto i : dl) {
        // res.push_back(i);
        std::cout << "hi" << std::endl;
    }
    // REQUIRE(res[0] == data[0]);
    // REQUIRE(res[1] == data[1]);
}
