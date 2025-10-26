#ifndef WOLFF_RNG_INTERFACE_HPP
#define WOLFF_RNG_INTERFACE_HPP

#include <concepts>
#include <random>

class IWolffRng
{
    virtual float getRandUniformFloat() = 0;
    virtual int geRandUniformX() = 0;
    virtual int geRandUniformY() = 0;
    virtual int geRandSpin() = 0;
    virtual ~IWolffRng() = default;
};

class WolffMt19937
{
    std::mt19937 m_rng{};
    std::uniform_int_distribution<int> m_intDistribX{};
    std::uniform_int_distribution<int> m_intDistribY{};
    std::uniform_real_distribution<int> m_spinDistrib{};
    std::uniform_real_distribution<float> m_floatDistrib{};
    // std::random_device
public:
    explicit WolffMt19937(std::random_device device, int width, int height)
        : m_rng{device()}, m_intDistribX{0, width-1}, m_intDistribY{0, height-1}, m_spinDistrib{0,1}, m_floatDistrib{0.0f, 1.0}
    {   
    }
    float getRandUniformFloat()
    {
        return m_floatDistrib(m_rng);
    }
    int geRandUniformX()
    {
        return m_intDistribX(m_rng);
    }
    int geRandUniformY()
    {
        return m_intDistribY(m_rng);
    }
    int getRandSpin()
    {
        return 1 - 2*m_spinDistrib(m_rng);
    }
    ~WolffMt19937() = default;
};

#endif