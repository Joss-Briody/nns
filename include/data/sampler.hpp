#include <iostream>

namespace Sampler {

    template <typename Dataset>
    class Sampler {
        Dataset dataset;
        public:
            Sampler(const Dataset& dataset_); 
    }
}