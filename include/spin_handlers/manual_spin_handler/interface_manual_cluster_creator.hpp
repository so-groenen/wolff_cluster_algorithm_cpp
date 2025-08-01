#ifndef IMANUAL_CLUSTER_CREATOR_HPP
#define IMANUAL_CLUSTER_CREATOR_HPP

#include "interface_cluster_creator.hpp" 

class IManualClusterCreator : public IClusterCreator
{
public:
    virtual void activateManualClusterCreator() = 0;
    virtual bool initClusterManually(IGuiArray2d& spinMatrix) = 0;
    virtual ~IManualClusterCreator()
    {
    }
};

#endif