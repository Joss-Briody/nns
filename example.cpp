#include <iostream>
#include <vector>

#include "data/mnist_reader.hpp"
#include "data/batcher.hpp"

typedef mnist::MnistDataset<uint8_t, uint8_t> Data;

int main(int argc, char* argv[]) {
    // load the mnist data
  
    BatchLoader<Data> batchLoader = BatchLoader<Data>(
        mnist::MnistReader<uint8_t, uint8_t>()
        .withBaseDirectory("/Users/Joss/Desktop/nns/mnist")
        .withTrainFiles("train-images-idx3-ubyte", "train-labels-idx1-ubyte")
        .withTestFiles("t10k-images-idx3-ubyte", "t10k-labels-idx1-ubyte")
        .read()
    );
    batchLoader.getDataset()->binarize(30);
    batchLoader.shuffleTrain();
    printArrays<uint8_t>(batchLoader.getDataset()->getTrainingHead());
}
