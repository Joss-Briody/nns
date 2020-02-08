#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <fstream>
#include <stdexcept>

#ifndef _MNIST_H
#define _MNIST_H

namespace mnist {

template <typename Pixel>
using Images = std::vector<std::vector<Pixel>>;

template <typename Label>
using Labels = std::vector<Label>;

template <typename Pixel>
std::vector<std::vector<Pixel>> readImages(const std::string& name);

template <typename Label>
std::vector<Label> readLabels(const std::string& name);

template <typename Pixel, typename Label>
struct Mnist {
  Images<Pixel> trainImages;
  Images<Pixel> testImages;
  Labels<Label> trainLabels;
  Labels<Label> testLabels;

  Mnist(std::vector<std::vector<Pixel>>&& trainImages_,
        std::vector<Label>&& trainLabels_,
        std::vector<std::vector<Pixel>>&& testImages_,
        std::vector<Label> testLabels_);

  Mnist<Pixel, Label>& binarize(double threshold = 30);

  std::pair<Images<Pixel>, Labels<Label>> getTrainingHead();
};

template <typename Pixel, typename Label>
class MnistReader {
 private:
  std::string folder;
  std::string trainImagesFilePath;
  std::string trainLabelsFilePath;
  std::string testImagesFilePath;
  std::string testLabelsFilePath;

 public:
  MnistReader& withBaseDirectory(const std::string& directory);
  MnistReader& withTrainFiles(const std::string& trainImages,
                              const std::string& trainLabels);
  MnistReader& withTestFiles(const std::string& testImages,
                             const std::string& testLabels);
  Mnist<Pixel, Label> read();
};

}  // namespace mnist

#include "src/data/mnist.tpp"
#endif