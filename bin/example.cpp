#include <iostream>
#include <vector>

#include "include/data/mnist.hpp"
#include "include/data/dataset.hpp"
#include "include/data/dataloader.hpp"
#include "include/data/sampler.hpp"
#include "include/data/batcher.hpp"

int main(int argc, char* argv[]) {

    typedef mnist::Mnist<uint8_t, uint8_t> MnistData;
    typedef std::vector<u_int8_t> x_type;
    typedef std::pair<x_type, uint8_t> Record;
    typedef std::vector<Record> VectorContainer;
    typedef data::Dataset<Record, VectorContainer> VectorDataset;

    const std::string DATA_DIR = "/Users/test/workspace/nns/dataset";

    // load the mnist data
    MnistData data = 
        mnist::MnistReader<uint8_t, uint8_t>()
        .withBaseDirectory(DATA_DIR)
        .withTrainFiles("train-images-idx3-ubyte", "train-labels-idx1-ubyte")
        .withTestFiles("t10k-images-idx3-ubyte", "t10k-labels-idx1-ubyte")
        .read()
        .binarize();

    data::Dataset<Record, VectorContainer> trainDataset(data.getTrainRecords());
    sampler::RandomSampler<Record, VectorContainer> trainSampler(trainDataset, 100);
    dataloader::VectorDataLoader trainDataLoader(trainSampler);

    int count = 0;
    for(const auto& item : trainDataLoader) {
        printRecords<uint8_t, uint8_t>(item);
        count++;
        if(count == 5) {
            break;
        }
    }

//     // batchLoader.shuffleTrain();
//     // // printArrays<uint8_t>(batchLoader.getDataset()->getTrainingHead());
//     // dl = dataloader::DataLoader<std::vector<int>>(std::vector<int> {1,2,3,4});
}
