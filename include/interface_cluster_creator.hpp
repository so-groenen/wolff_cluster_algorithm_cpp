#ifndef INTERFACE_CLUSTER_CREATOR
#define INTERFACE_CLUSTER_CREATOR

#include <random>
#include "interface_gui_array_2d.hpp"

class IClusterCreator
{
public:
    virtual void createCluster(IGuiArray2d& raySpin, std::mt19937& rng, float temperature) = 0;
    virtual ~IClusterCreator()
    {
    };
};

#endif