#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>

#include <math.h>

#ifndef _DATASET_H
#define _DATASET_H

template <typename Dataset>
class BatchLoader {
private:
    std::shared_ptr<Dataset> dataset;
    int currentEpoch;
    int batchNumber;
    int batchSize;

public:
    BatchLoader(std::unique_ptr<Dataset> &&dataset_);
    std::shared_ptr<Dataset> getDataset();
    void shuffleTrain();
    void sampleTrainBatch();
    void sampleTrain();
    void sampleTestBatch();
    void sampleTest();
    int getBatchSize();
};

template <typename Container>
void printMax(Container &values);

template <typename T, typename V>
void printArrays(std::pair<std::vector<std::vector<T>>, std::vector<V>> &&values);

// template <typename Dataset>
// BatchLoader<Dataset>::BatchLoader(std::unique_ptr<Dataset> &&dataset_)
// {
//     dataset = std::move(dataset_);
// }

// template <typename Dataset>
// std::shared_ptr<Dataset> BatchLoader<Dataset>::getDataset() { return dataset; }

// template <typename Dataset>
// void BatchLoader<Dataset>::shuffleTrain()
// {
//     std::cout << "hello" << std::endl;
//     // std::vector<unsigned int> indexes(dataset->training_images.size());
//     // std::iota(indexes.begin(), indexes.end(), 0);
//     // std::random_device rng;
//     // std::mt19937 urng(rng());
//     // std::shuffle(indexes.begin(), indexes.end(), urng);
//     // for (size_t i = 0; i < dataset->training_images.size(); ++i)
//     // {
//     //     std::swap(dataset->training_images[i], dataset->training_images[indexes[i]]);
//     //     std::swap(dataset->training_labels[i], dataset->training_labels[indexes[i]]);
//     // }
// }

// template <typename Container>
// void printMax(Container &values)
// {
//     for (auto &vec : values)
//     {
//         std::cout << " Max is: " + std::to_string(*std::max_element(vec.begin(), vec.end()));
//     }
// }

// template <typename T, typename V>
// void printArrays(std::pair<std::vector<std::vector<T>>, std::vector<V>> &&values)
// {
//     auto printIms = [](const std::vector<T> &v) {
//         unsigned int dim = sqrt(v.size());
//         for (size_t i = 0; i < v.size(); ++i)
//         {
//             if (i % dim == 0)
//             {
//                 std::cout << std::endl;
//             }
//             auto s = v[i] == 1 ? "X" : ".";
//             std::string ch(s);
//             std::cout << ch << " ";
//         }
//     };
//     std::for_each(values.first.begin(), values.first.end(), printIms);
//     std::for_each(values.second.begin(), values.second.end(),
//                   [](const V &v) { std::cout << std::to_string(v) << std::endl; });
// }

#include "src/data/batcher.tpp"
#endif