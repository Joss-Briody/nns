#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <fstream>
#include <stdexcept>

namespace mnist {

bool fileExists(const std::string &fileName)
{
    std::ifstream f(fileName.c_str());
    return f.good();
}

void checkFileExists(const std::string &name)
{
    if (!fileExists(name))
    {
        throw std::invalid_argument("File does not exists: " + name);
    }
}

inline uint32_t readHeader(const std::unique_ptr<char[]> &buffer, size_t position)
{
    auto header = reinterpret_cast<uint32_t *>(buffer.get());
    auto value = *(header + position);
    return (value << 24) | ((value << 8) & 0x00FF0000) | ((value >> 8) & 0X0000FF00) | (value >> 24);
}

inline std::unique_ptr<char[]> readBinaryFile(const std::string &path)
{
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary | std::ios::ate);
    if (!f)
    {
        std::cout << "Error opening file" << std::endl;
        return {};
    }
    auto size = f.tellg();
    std::unique_ptr<char[]> buffer(new char[size]);

    f.seekg(0, std::ios::beg);
    f.read(buffer.get(), size);
    f.close();
    return buffer;
}

template <typename Pixel = uint8_t>
std::vector<std::vector<Pixel>> readImages(const std::string &name)
{
    auto buffer = readBinaryFile(name);
    if (buffer) {
        auto count = readHeader(buffer, 1);
        auto rows = readHeader(buffer, 2);
        auto columns = readHeader(buffer, 3);
        std::cout << "Count: " + std::to_string(count) << std::endl;
        std::cout << "Number of rows: " + std::to_string(rows) << std::endl;
        std::cout << "Number of columns: " + std::to_string(columns) << std::endl;

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

template <typename Label = uint8_t>
std::vector<Label> readLabels(const std::string &name)
{
    auto buffer = readBinaryFile(name);
    if (buffer)
    {
        auto count = readHeader(buffer, 1);

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

template <typename Pixel = uint8_t, typename Label = uint8_t>
struct MnistDataset
{
    std::vector<std::vector<Pixel>> training_images; ///< The training images
    std::vector<std::vector<Pixel>> test_images;     ///< The test images
    std::vector<Label> training_labels;              ///< The training labels
    std::vector<Label> test_labels;

    void binarize(const double& threshold) {
        auto binarize_images = [&threshold](std::vector<Pixel>& image) {
            for(auto& v : image) {
                v = v > threshold ? 1.0 : 0.0;
            }
        };
        std::for_each(training_images.begin(), training_images.end(), binarize_images);
        std::for_each(test_images.begin(), test_images.end(), binarize_images);
    };

    std::pair<std::vector<std::vector<Pixel>>, std::vector<Label>> getTrainingHead() {
        std::vector<std::vector<Pixel>> tmpImages(10);
        std::vector<Label> tmpLabels(10);
        std::copy_n(training_images.begin(), 10, tmpImages.begin());
        std::copy_n(training_labels.begin(), 10, tmpLabels.begin());
        return std::make_pair(tmpImages, tmpLabels);
    }
};


template <typename Pixel = uint8_t, typename Label = uint8_t>
class MnistReader
{
private:
    std::string folder;
    std::string trainImagesFilePath;
    std::string trainLabelsFilePath;
    std::string testImagesFilePath;
    std::string testLabelsFilePath;

public:
    MnistReader();
    MnistReader withBaseDirectory(const std::string &directory);
    MnistReader withTrainFiles(const std::string &trainImages, const std::string& trainLabels);
    MnistReader withTestFiles(const std::string &trainImages, const std::string& trainLabels);
    std::unique_ptr<MnistDataset<Pixel, Label>> read();
};

template <typename Pixel, typename Label>
std::unique_ptr<MnistDataset<Pixel, Label>> MnistReader<Pixel, Label>::read(){
    MnistDataset<Pixel, Label> data;
    data.training_images = readImages<Pixel>(trainImagesFilePath);
    data.training_labels = readLabels<Label>(trainLabelsFilePath);
    data.test_images = readImages<Pixel>(testImagesFilePath);
    data.test_labels = readLabels<Label>(testLabelsFilePath);
    std::cout << "Nbr of training images = " << data.training_images.size() << std::endl;
    std::cout << "Nbr of training labels = " << data.training_labels.size() << std::endl;
    std::cout << "Nbr of test images = " << data.test_images.size() << std::endl;
    std::cout << "Nbr of test labels = " << data.test_labels.size() << std::endl;
    return std::make_unique<MnistDataset<Pixel, Label>>(data);
}

template <typename Pixel, typename Label>
MnistReader<Pixel, Label>::MnistReader()
{
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
    checkFileExists(trainImagesFilePath);
    checkFileExists(trainLabelsFilePath);
    return *this;
}

template <typename Pixel, typename Label>
MnistReader<Pixel, Label> MnistReader<Pixel, Label>::withTestFiles(const std::string &testImages, const std::string &testLabels)
{
    testImagesFilePath = folder + "/" + testImages;
    testLabelsFilePath = folder + "/" + testLabels;
    checkFileExists(testImagesFilePath);
    checkFileExists(testLabelsFilePath);
    return *this;
}

} // namespace mnist