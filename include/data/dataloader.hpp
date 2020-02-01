#include <iostream>

namespace dataloader 
{
    template <typename Dataset, typename Sampler>
    class DataLoader {
    private:
        const Dataset& dataset;
        const Sampler& sampler;

    public:
        DataLoader(const Dataset &dataset, const Sampler &sampler);
    };

} // namespace dataloader
