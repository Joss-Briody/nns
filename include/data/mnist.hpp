#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <fstream>
#include <stdexcept>

#ifndef _MNIST_H
#define _MNIST_H

namespace mnist {

    template <typename Pixel>
    std::vector<std::vector<Pixel>> readImages(const std::string &name);

    template <typename Label>
    std::vector<Label> readLabels(const std::string &name);

    template <typename Pixel, typename Label>
    struct Mnist {
        std::vector<std::vector<Pixel>> training_images;
        std::vector<std::vector<Pixel>> test_images;
        std::vector<Label> training_labels;
        std::vector<Label> test_labels;

        void binarize(const double &threshold);

        std::pair<std::vector<std::vector<Pixel>>, std::vector<Label>> getTrainingHead();
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
        MnistReader withBaseDirectory(const std::string &directory);
        MnistReader withTrainFiles(const std::string &trainImages, const std::string &trainLabels);
        MnistReader withTestFiles(const std::string &testImages, const std::string &testLabels);
        std::unique_ptr<Mnist<Pixel, Label>> read();
    };

} // namespace mnist

#include "src/data/mnist.tpp"
#endif