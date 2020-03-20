#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <fstream>
#include <stdexcept>
#include <thread>
#include <future>

#include "include/data/mnist.hpp"
#include "include/data/io_utils.hpp"

namespace mnist {

template <typename Pixel>
std::vector<std::vector<Pixel>> readImages(const std::string &name) {
  auto buffer = io::readBinaryFile(name);
  if (buffer) {
    auto count = io::readHeader(buffer, 1);
    auto rows = io::readHeader(buffer, 2);
    auto columns = io::readHeader(buffer, 3);
    auto image_buffer = reinterpret_cast<unsigned char *>(buffer.get() + 16);
    std::vector<std::vector<Pixel>> images;
    images.reserve(count);
    for (size_t i = 0; i < count; ++i) {
      images.emplace_back(rows * columns);
      for (size_t j = 0; j < rows * columns; ++j) {
        auto pixel = *image_buffer++;
        images[i][j] = static_cast<Pixel>(pixel);
      }
    }
    return images;
  }
  return {};
}

template <typename Label>
std::vector<Label> readLabels(const std::string &name) {
  auto buffer = io::readBinaryFile(name);
  if (buffer) {
    auto count = io::readHeader(buffer, 1);
    auto label_buffer = reinterpret_cast<unsigned char *>(buffer.get() + 8);
    std::vector<Label> labels(count);
    labels.reserve(count);
    for (size_t i = 0; i < count; ++i) {
      auto label = *label_buffer++;
      labels[i] = static_cast<Label>(label);
    }
    return labels;
  }
  return {};
}

template <typename Pixel, typename Label>
Mnist<Pixel, Label>::Mnist(std::vector<std::vector<Pixel>> &&trainImages_,
                           std::vector<Label> &&trainLabels_,
                           std::vector<std::vector<Pixel>> &&testImages_,
                           std::vector<Label> testLabels_) {
  trainImages = std::move(trainImages_);
  trainLabels = std::move(trainLabels_);
  testImages = std::move(testImages_);
  testLabels = std::move(testLabels_);
}

template <typename Pixel, typename Label>
Mnist<Pixel, Label>& Mnist<Pixel, Label>::binarize(double threshold) {
  auto binarize = [&threshold](std::vector<Pixel> &image) {
    for (auto &v : image) {
      v = v > threshold ? 1.0 : 0.0;
    }
  };
  std::for_each(trainImages.begin(), trainImages.end(), binarize);
  std::for_each(testImages.begin(), testImages.end(), binarize);
  return *this;
}

template <typename Pixel, typename Label>
std::vector<std::pair<std::vector<Pixel>, Label>> Mnist<Pixel, Label>::getTrainRecords(size_t numRecords) {
    size_t num = numRecords == 0 ? trainImages.size() : numRecords;
    std::vector<std::pair<std::vector<Pixel>, Label>> records(num);
    for(size_t i=0; i<num; ++i) {
        records[i] = std::make_pair(trainImages[i], trainLabels[i]);
    }
    return records;
}

template <typename Pixel, typename Label>
std::vector<std::pair<std::vector<Pixel>, Label>> Mnist<Pixel, Label>::getTestRecords() {
    std::vector<std::pair<std::vector<Pixel>, Label>> records(testImages.size());
    for(size_t i=0; i<testImages.size(); ++i) {
        records[i] = std::make_pair(testImages[i], testLabels[i]);
    }
    return records;
}

// template <typename Pixel, typename Label>
// std::pair<std::vector<std::vector<Pixel>>, std::vector<Label>>
// Mnist<Pixel, Label>::getTrainingHead() {
//   std::vector<std::vector<Pixel>> tmpImages(10);
//   std::vector<Label> tmpLabels(10);
//   std::copy_n(trainImages.begin(), 10, tmpImages.begin());
//   std::copy_n(trainLabels.begin(), 10, tmpLabels.begin());
//   return std::make_pair(tmpImages, tmpLabels);
// }

template <typename Pixel, typename Label>
MnistReader<Pixel, Label> &MnistReader<Pixel, Label>::withBaseDirectory(
    const std::string &directory) {
  folder = directory;
  return *this;
}

template <typename Pixel, typename Label>
MnistReader<Pixel, Label> &MnistReader<Pixel, Label>::withTrainFiles(
    const std::string &trainImages, const std::string &trainLabels) {
  trainImagesFilePath = folder + "/" + trainImages;
  trainLabelsFilePath = folder + "/" + trainLabels;
  io::checkFileExists(trainImagesFilePath);
  io::checkFileExists(trainLabelsFilePath);
  return *this;
}

template <typename Pixel, typename Label>
MnistReader<Pixel, Label> &MnistReader<Pixel, Label>::withTestFiles(
    const std::string &testImages, const std::string &testLabels) {
  testImagesFilePath = folder + "/" + testImages;
  testLabelsFilePath = folder + "/" + testLabels;
  io::checkFileExists(testImagesFilePath);
  io::checkFileExists(testLabelsFilePath);
  return *this;
}

template <typename Pixel, typename Label>
Mnist<Pixel, Label> MnistReader<Pixel, Label>::read() {
  auto trainImages = std::async(readImages<Pixel>, trainImagesFilePath);
  auto trainLabels = std::async(readLabels<Label>, trainLabelsFilePath);
  auto testImages = std::async(readImages<Pixel>, testImagesFilePath);
  auto testLabels = std::async(readLabels<Label>, testLabelsFilePath);
  return Mnist<Pixel, Label>(
      std::move(trainImages.get()), std::move(trainLabels.get()),
      std::move(testImages.get()), std::move(testLabels.get()));
}

}  // namespace mnist