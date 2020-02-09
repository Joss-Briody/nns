#include <iostream>
#include <vector>
#include <utility>
#include "include/data/sampler.hpp"
#include "include/data/iterator.hpp"

#ifndef _DATALOADER_H
#define _DATALOADER_H

using UPairRecord = std::pair<std::vector<uint8_t>, size_t>;
using UPairContainer = std::vector<UPairRecord>;
using UPairSampler = sampler::RandomSampler<UPairRecord, UPairContainer>;
using UPairIterable = iterator::Iterable<UPairRecord, UPairSampler>;


namespace dataloader {

// using FPairRecord = std::pair<std::vector<float>, size_t>;
// using FPairContainer = std::vector<FPairRecord>;
// using FPairSampler = sampler::RandomSampler<FPairRecord, FPairContainer>;
// using FPairIterable = iterator::Iterable<FPairRecord, FPairSampler>;

class VectorDataLoader : public UPairIterable {
 public:
  constexpr VectorDataLoader(UPairSampler& sampler_)
      : UPairIterable(sampler_, 0, sampler_.size()) {}
  
//   constexpr VectorDataLoader(FPairSampler& sampler_)
//       : FPairIterable(sampler_, 0, sampler_.size()) {}
};

}  // namespace dataloader

#endif