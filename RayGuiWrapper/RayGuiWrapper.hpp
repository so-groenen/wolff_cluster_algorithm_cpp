
#ifndef RAYGUI_WRAPPER
#define RAYGUI_WRAPPER

#include <cstring>
#include <memory>
#include <cmath>
namespace ray
{
    #include <raylib.h>
}

#ifndef RAYGUI_IMPLEMENTATION
#define RAYGUI_IMPLEMENTATION
#endif

namespace ray
{
    #include <raygui.h>
}

using ray::SLIDER_PADDING;
using ray::SLIDER;
using ray::DEFAULT;
using ray::TEXT_SIZE;


class BaseGui
{
    ray::Rectangle m_rect;
    float m_xStart{};
    float m_yStart{};
    float m_width{};
    float m_height{};
    float m_xOffset{};
public:
    BaseGui(float xStart, float yStart, float width, float height)
        :   m_xStart(xStart), m_yStart(yStart), m_width(width), m_height(height)
    {
        m_xOffset = 0;
    }
    ~BaseGui() = default;
    void setXoffset(float xOffset)
    {
        m_xOffset = xOffset;
    }
    const ray::Rectangle& getRect() const
    {
        return m_rect;
    }
    void setRect()
    {
        m_rect = ray::Rectangle{m_xStart + m_xOffset, m_yStart, m_width, m_height};
    }
};

class RayToggleSlider : public BaseGui
{
    char m_switchName[64];
public:
    RayToggleSlider(float xStart, float yStart, float width, float height)
        : BaseGui(xStart, yStart, width, height)
    {
        setRect();
        strcpy(m_switchName, "ON;OFF");
    } 
    ~RayToggleSlider() = default;
    void setSwitchName(const char* name)
    {
        if(strlen(name) >= 64)
        {
            throw std::out_of_range("Name to long");
        }
        strcpy(m_switchName, name);
    }
    template <typename T>
    void activateAndDrawEnum(T& enumToggle) const
    {
        int toggle = static_cast<int>(enumToggle);
        activateAndDraw(toggle);
        enumToggle = static_cast<T>(toggle);
    }
    void activateAndDraw(int& toggle) const
    {
        if (toggle < 0 || toggle > 1)
        {
            throw std::out_of_range("value must be 0 or 1");
        }
        ray::GuiSetStyle(SLIDER, SLIDER_PADDING, 1);
        ray::GuiToggleSlider(getRect(), m_switchName, &toggle);
        ray::GuiSetStyle(SLIDER, SLIDER_PADDING, 0);
    }
};



class RaySliderBar : public BaseGui
{
    char m_LeftText[64];
    float m_max = 10;
    float m_min = 0.01;
public:
    RaySliderBar(float xStart, float yStart, float width, float height)
        :   BaseGui(xStart, yStart, width, height)
    {
        strcpy(m_LeftText, "default");
        setXoffset((float)ray::GetTextWidth(m_LeftText));
        setRect();
    } 
    ~RaySliderBar() = default;
    void setSlideLimits(float min, float max)
    {
        m_min = min;
        m_max = max;
    }
    void setLeftText(const char* leftText)
    {
        if(strlen(leftText) >= 64)
        {
            throw std::out_of_range("Name to long");
        }
        strcpy(m_LeftText, leftText);
        setXoffset((float)ray::GetTextWidth(m_LeftText));
        setRect();
    }
    void activateAndDraw(float& slide) const
    {
        ray::GuiSliderBar(getRect(), m_LeftText, ray::TextFormat("%.2f", slide), &slide, m_min, m_max);
    }
};


class RayText
{
    float m_xStart;
    float m_yStart;
    int m_font;
    int m_xOffset = 0;
    bool m_isJustified{false};
    ray::Color m_textColor;
public:
    explicit RayText(float x, float y, ray::Color color)
        : m_xStart{x}, 
        m_yStart{y},
        m_font{ray::GuiGetStyle(ray::DEFAULT, ray::TEXT_SIZE)},
        m_textColor{color}
    {
    }
    ~RayText() = default;
    RayText& setFontManual(int fontSize)
    {
        m_font = fontSize;
        return *this;
    }
    RayText& setFontAuto()
    {
        m_font = ray::GuiGetStyle(ray::DEFAULT, ray::TEXT_SIZE);
        return *this;
    }
    RayText& justify(bool isJustified)
    {
        m_isJustified = isJustified;
        return *this;
    }
    void writeAnddraw(const char* text) 
    {
        auto oldfont = ray::GuiGetStyle(ray::DEFAULT, ray::TEXT_SIZE);
        ray::GuiSetStyle(ray::DEFAULT, ray::TEXT_SIZE, m_font);

        
        float width  = (float)ray::GetTextWidth(text);
        float height = 0.1f*(float)ray::GetScreenHeight(); 
        if (m_isJustified)
        {
            m_xOffset = ray::GetTextWidth(text)/2;
            m_xStart = ray::GetScreenWidth()/2;
        }
        BaseGui base{m_xStart, m_yStart, width, height};
        base.setXoffset(-m_xOffset);
        // ray::GuiDrawText(text, base.getRect(), ray::TEXT_ALIGN_RIGHT, m_textColor);
        ray::DrawText(text, m_xStart - m_xOffset, m_yStart, ray::GuiGetStyle(ray::DEFAULT, ray::TEXT_SIZE), m_textColor);
        
        ray::GuiSetStyle(ray::DEFAULT, ray::TEXT_SIZE, oldfont); // rayGui defaut
    }
};





#endif