#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include <utility>
#include <math.h>

#ifndef _BATCHER_H
#define _BATCHER_H

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


#include "src/data/batcher.tpp"
#endif