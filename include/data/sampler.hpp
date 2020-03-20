#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <numeric>
#include <random>
#include <math.h>

#include "include/data/dataset.hpp"

#ifndef _SAMPLER_H
#define _SAMPLER_H

namespace sampler {

std::vector<size_t> createIndices(size_t datasetSize) {
  std::vector<size_t> indexes(datasetSize);
  std::iota(indexes.begin(), indexes.end(), 0);
  std::random_device rng;
  std::mt19937 urng(rng());
  std::shuffle(indexes.begin(), indexes.end(), urng);
  return indexes;
};

std::unordered_map<size_t, std::vector<size_t>> createBatchMappings(
  size_t batchSize, size_t datasetSize) {
  size_t begin = 0;
  size_t end = std::min(batchSize, datasetSize);
  size_t numBatches = ceil(datasetSize / (double)batchSize);
  std::unordered_map<size_t, std::vector<size_t>> batchMappings;
  for (size_t i = 0; i < numBatches; ++i) {
    std::vector<size_t> tmp(end - begin);
    std::iota(tmp.begin(), tmp.end(), begin);
    batchMappings[i] = std::move(tmp);
    begin = end;
    end = std::min(end + batchSize, datasetSize);
  }
  return batchMappings;
};

template <typename Record, typename Container>
class RandomSampler {
  data::Dataset<Record, Container>& dataset;
  size_t batchSize;
  std::vector<size_t> indexes;
  std::unordered_map<size_t, std::vector<size_t>> batchMappings;

 public:
  RandomSampler(data::Dataset<Record, Container>& dataset_, size_t batchSize_)
      : dataset(dataset_),
        batchSize(batchSize_),
        indexes(createIndices(dataset_.size())),
        batchMappings(createBatchMappings(batchSize_, dataset_.size())) {}

  size_t size() { return batchMappings.size(); }

  Container operator[](const unsigned int& i) {
    size_t thisBatchSize = batchMappings[i].size();
    Container batch(thisBatchSize);
    for (size_t j = 0; j < thisBatchSize; ++j) {
      batch[j] = dataset[indexes[batchMappings[i][j]]];
    }
    return batch;
  }
};
}

#endif