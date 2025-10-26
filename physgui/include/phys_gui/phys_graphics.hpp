#ifndef PHYS_GRAPHICS_HPP
#define PHYS_GRAPHICS_HPP

#include <iostream>
#include <vector>

 

#ifdef __EMSCRIPTEN__
#include <SDL_opengles2.h>
#else
#include "glad/glad.h"
#endif
#include "imgui.h"


namespace PhysGraphics  
{
    using byte = unsigned char;

 


#if defined(IMGUI_IMPL_OPENGL_ES2)
    inline bool g_opengl_context{true};
#else
    inline bool g_opengl_context{false};
    inline void LoadOpenGl(GLADloadproc GetProcAddress)
    {
        if(!gladLoadGLLoader(GetProcAddress))
        {
            throw std::runtime_error("OpenGL: Failure Loading OpenGL functions");
        }
        else
        {
            g_opengl_context = true;
        }
    }
#endif


    class Image
    { 
        int m_format{GL_RGBA};

    protected: 
        std::vector<ImU32> m_data{}; 
        void FillImage(ImU32 color)
        {
            for (size_t x = 0; x < width; x++)
            {
                for (size_t y = 0; y < height; y++)
                {
                    m_data[x+y*width] = color;
                }   
            }
        }
    public:
        const size_t width{};
        const size_t height{};
        Image(size_t w, size_t h, ImU32 color)
            : width{w}, height{h}, m_data(w*h)
        {
            FillImage(color);
        }
        int Format() const
        {
            return m_format;
        }
        const byte* Bytes() const
        {
            return (byte*) m_data.data();
        } 
        size_t Size() const 
        {
            return sizeof(ImU32)*m_data.size();
        } 
    };

    class CheckboardImage : public Image
    {
        size_t m_sqr_size{};
        public:
            CheckboardImage(size_t w, size_t h, size_t sqr_size, ImU32 color1, ImU32 color2)
               :  Image(sqr_size*w, sqr_size*h, 0), m_sqr_size{sqr_size}
            {
                PaintCheckboard(color1, color2);
            }   
            void PaintCheckboard(ImU32 color1, ImU32 color2)
            {
                size_t h{height/m_sqr_size};
                size_t w{width/m_sqr_size};

                for (size_t y = 0; y < h; y++)
                {
                    for (size_t x = 0; x < w; x++)
                    {
                        ImU32 color = (x%2==0)? color1 : color2;
                        Paint(x, y, color);
                    }
                    ImU32 temp{color1};
                    color1 = color2;
                    color2 = temp;
                    // swap(colorA, colorB);
                }
            }
            size_t SquareSize() const 
            {
                return m_sqr_size;
            }
            ImU32 At(size_t x, size_t y) const
            {
                return m_data[(x*m_sqr_size) + (y*m_sqr_size)*width];
            }
            void Paint(size_t x, size_t y, ImU32 color)
            {
                for (size_t dx = 0; dx < m_sqr_size; dx++)
                {
                    for (size_t dy = 0; dy < m_sqr_size; dy++)
                    {
                        m_data[(x*m_sqr_size + dx) + (y*m_sqr_size + dy)*width] = color;
                    }
                }
            }

        
    };
    enum class Filter
    {
        Linear,
        Nearest
    };

    class Texture
    {
        GLuint m_image_texture{};
        ImTextureID m_id{};
    public:
        void DeleteTexture()
        {
            glDeleteTextures(1, &m_image_texture);
        }
        Texture& operator= (const Texture& other)
        {
            m_image_texture = other.m_image_texture;
            return *this;
        }
        const size_t width{};
        const size_t height{};
        Texture(const Image& img, Filter filter = Filter::Nearest)
            : width{img.width}, height{img.height}
        {
            if(!g_opengl_context)
            {
                throw std::runtime_error("No Glad openGL context found!");
            }

            glGenTextures(1, &m_image_texture);
            glBindTexture(GL_TEXTURE_2D, m_image_texture);
            
            m_id = (ImTextureID)(intptr_t)m_image_texture;

            switch(filter)
            {
                case Filter::Linear:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                    break;
                case Filter::Nearest:
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                    break;
                }

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

#ifndef __EMSCRIPTEN__ 
            // glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // images is tightly packed by default, we do not need to force it in emscripten
            glPixelStorei(GL_UNPACK_ROW_LENGTH, 0); // images is tightly packed by default, we do not need to force it in emscripten
#endif
            // 1 spin = 4 bytes (rgba) which we can 
            glTexImage2D(GL_TEXTURE_2D, 0, img.Format(), width, height, 0, img.Format(), GL_UNSIGNED_BYTE, img.Bytes());
            // glGenerateMipmap(GL_TEXTURE_2D);
        }
        ImTextureID Id() const 
        {
            return m_id;
        }
        void Bind()
        {
            glBindTexture(GL_TEXTURE_2D, m_image_texture);
        }
        ImVec2 Size() const 
        {
            return ImVec2{static_cast<float>(width), static_cast<float>(height)};
        }
        bool Update(const Image& img)
        {
            if( img.height != height || img.width  != width)
            {
                return false;
            }
            glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, img.width, img.height, img.Format(),  GL_UNSIGNED_BYTE, img.Bytes());
            // glTexImage2D(GL_TEXTURE_2D, 0, img.format(), img.width, img.height, 0, img.format(), GL_UNSIGNED_BYTE, img.bytes());
            return true;
        }
        void Draw(const ImVec2& p_min, const ImVec2& p_max, const ImVec2& uv_min = ImVec2(0, 0), const ImVec2& uv_max = ImVec2(1, 1), ImU32 col = IM_COL32_WHITE)
        {
            ImGui::GetWindowDrawList()->AddImage(m_id, p_min, p_max, uv_min, uv_max, col);
        }
        ~Texture()
        {
            printf("DEBUG: Texture %u deleted\n.", m_image_texture);
            DeleteTexture();
        }
    };
    


}
#endif