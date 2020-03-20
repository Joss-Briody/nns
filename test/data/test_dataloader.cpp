#include <utility>
#include <vector>
#include <unordered_map>
#include "include/tests/catch.hpp"
#include "include/data/dataloader.hpp"
#include "include/data/dataset.hpp"
#include "include/data/sampler.hpp"

TEST_CASE("DataLoader can be iterated", "[dataloader]") {
    typedef std::vector<u_int8_t> x_type;
    typedef std::pair<x_type, u_int8_t> Record;
    typedef std::vector<Record> VectorContainer;
    typedef data::Dataset<Record, VectorContainer> VectorDataset;
    VectorContainer data = {
        std::make_pair<x_type, u_int8_t>({1, 2, 3}, 1),
        std::make_pair<x_type, u_int8_t>({4, 5, 6}, 2),
        std::make_pair<x_type, u_int8_t>({1, 2, 3}, 3),
        std::make_pair<x_type, u_int8_t>({4, 5, 6}, 4),
        std::make_pair<x_type, u_int8_t>({1, 2, 3}, 5),
        std::make_pair<x_type, u_int8_t>({4, 5, 6}, 6),
    };
    std::unordered_map<u_int8_t, x_type> expected;
    for(const auto& item: data) {
        expected[item.second] = item.first;
    }
    VectorDataset dataset(data);
    sampler::RandomSampler<Record, VectorContainer> sampler(dataset, 3);
    dataloader::VectorDataLoader dataLoader(sampler);

    std::vector<std::vector<Record>> res;
    for(const auto& item : dataLoader) {
        for(const auto& i : item) {
             REQUIRE(expected[i.second] == i.first);
        }
    }
}
