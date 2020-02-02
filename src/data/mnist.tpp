#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <fstream>
#include <stdexcept>

#include "include/data/mnist.hpp"
#include "include/data/io_utils.hpp"

namespace mnist {

template <typename Pixel>
std::vector<std::vector<Pixel>> readImages(const std::string &name)
{
    auto buffer = io::readBinaryFile(name);
    if (buffer)
    {
        auto count = io::readHeader(buffer, 1);
        auto rows = io::readHeader(buffer, 2);
        auto columns = io::readHeader(buffer, 3);
        auto image_buffer = reinterpret_cast<unsigned char *>(buffer.get() + 16);
        std::vector<std::vector<Pixel>> images;
        images.reserve(count);
        for (size_t i = 0; i < count; ++i)
        {
            images.emplace_back(rows * columns);
            for (size_t j = 0; j < rows * columns; ++j)
            {
                auto pixel = *image_buffer++;
                images[i][j] = static_cast<Pixel>(pixel);
            }
        }
        return images;
    }
    return {};
}

template <typename Label>
std::vector<Label> readLabels(const std::string &name)
{
    auto buffer = io::readBinaryFile(name);
    if (buffer)
    {
        auto count = io::readHeader(buffer, 1);
        auto label_buffer = reinterpret_cast<unsigned char *>(buffer.get() + 8);
        std::vector<Label> labels(count);
        labels.reserve(count);
        for (size_t i = 0; i < count; ++i)
        {
            auto label = *label_buffer++;
            labels[i] = static_cast<Label>(label);
        }
        return labels;
    }
    return {};
}

template <typename Pixel, typename Label>
void Mnist<Pixel, Label>::binarize(const double &threshold) 
{
    auto binarize_images = [&threshold](std::vector<Pixel> &image) {
        for (auto &v : image)
        {
            v = v > threshold ? 1.0 : 0.0;
        }
    };
    std::for_each(training_images.begin(), training_images.end(), binarize_images);
    std::for_each(test_images.begin(), test_images.end(), binarize_images);
}

template <typename Pixel, typename Label>
std::pair<std::vector<std::vector<Pixel>>, std::vector<Label>> Mnist<Pixel, Label>::getTrainingHead()
{
    std::vector<std::vector<Pixel>> tmpImages(10);
    std::vector<Label> tmpLabels(10);
    std::copy_n(training_images.begin(), 10, tmpImages.begin());
    std::copy_n(training_labels.begin(), 10, tmpLabels.begin());
    return std::make_pair(tmpImages, tmpLabels);
    
}

template <typename Pixel, typename Label>
MnistReader<Pixel, Label> MnistReader<Pixel, Label>::withBaseDirectory(const std::string &directory)
{
    folder = directory;
    return *this;
}

template <typename Pixel, typename Label>
MnistReader<Pixel, Label> MnistReader<Pixel, Label>::withTrainFiles(const std::string &trainImages, const std::string &trainLabels)
{
    trainImagesFilePath = folder + "/" + trainImages;
    trainLabelsFilePath = folder + "/" + trainLabels;
    io::checkFileExists(trainImagesFilePath);
    io::checkFileExists(trainLabelsFilePath);
    return *this;
}

template <typename Pixel, typename Label>
MnistReader<Pixel, Label> MnistReader<Pixel, Label>::withTestFiles(const std::string &testImages, const std::string &testLabels)
{
    testImagesFilePath = folder + "/" + testImages;
    testLabelsFilePath = folder + "/" + testLabels;
    io::checkFileExists(testImagesFilePath);
    io::checkFileExists(testLabelsFilePath);
    return *this;
}

template <typename Pixel, typename Label>
std::unique_ptr<Mnist<Pixel, Label>> MnistReader<Pixel, Label>::read()
{
    Mnist<Pixel, Label> data;
    data.training_images = readImages<Pixel>(trainImagesFilePath);
    data.training_labels = readLabels<Label>(trainLabelsFilePath);
    data.test_images = readImages<Pixel>(testImagesFilePath);
    data.test_labels = readLabels<Label>(testLabelsFilePath);
    return std::make_unique<Mnist<Pixel, Label>>(data);
}

} // namespace mnist