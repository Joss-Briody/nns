#include <iostream>
#include <vector>
#include <utility>
#include "include/data/sampler.hpp"
#include "include/data/iterator.hpp"

#ifndef _DATALOADER_H
#define _DATALOADER_H

using PairRecord = std::pair<std::vector<uint8_t>, size_t>;
using PairContainer = std::vector<PairRecord>;
using PairSampler = sampler::RandomSampler<PairRecord, PairContainer>;
using PairIterable = iterator::BatchIterable<PairRecord, PairSampler>;


namespace dataloader {

// using FPairRecord = std::pair<std::vector<float>, size_t>;
// using FPairContainer = std::vector<FPairRecord>;
// using FPairSampler = sampler::RandomSampler<FPairRecord, FPairContainer>;
// using FPairIterable = iterator::Iterable<FPairRecord, FPairSampler>;

class VectorDataLoader : public PairIterable {
 public:
  constexpr VectorDataLoader(PairSampler& sampler_)
      : PairIterable(sampler_, 0, sampler_.size()) {}
  
//   constexpr VectorDataLoader(FPairSampler& sampler_)
//       : FPairIterable(sampler_, 0, sampler_.size()) {}
};

}  // namespace dataloader

#endif