#include "phys_gui/phys_runner.hpp" 
#include "phys_gui/phys_graphics.hpp"
#include "phys_gui/phys_gui.hpp" 
#include "interface_gui_array_2d.hpp"
#include "wolff_finite_state_machine.hpp"
#include "imgui_array_2d/imgui_array_2d.hpp"
#include <random>
#include <functional>
#include <chrono>

using imgui_array_2d::MyGuiArray;
using PhysRunner::IPhysGuiApp;

inline uint32_t Seed()
{
    return static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count());
}

constexpr size_t NX             {512};
constexpr size_t NY             {256};   
constexpr size_t VRTL_SQR_SIZE  {2}; 
constexpr float ZOOM_RATIO      {1.1f};
constexpr float MIN_TEMP        {0.0f}; 
constexpr float MAX_TEMP        {5.0f};
constexpr float SQR_SIZE        {ZOOM_RATIO*static_cast<float>(VRTL_SQR_SIZE)};
const ImU32 SPIN_UP_COLOR       {ImColor(120, 185, 181, 255)};
const ImU32 SPIN_DOWN_COLOR     {ImColor(50, 10, 107, 255)};
const ImU32 MOUSE_COLOR         {ImColor(255, 10, 10, 255)};

class WolffSimulation : public IPhysGuiApp
{
    PhysGraphics::CheckboardImage checkboard_img{NX, NY, VRTL_SQR_SIZE, SPIN_UP_COLOR, SPIN_DOWN_COLOR};
    PhysGraphics::Texture checkboard_texture    {checkboard_img};
    MyGuiArray spin_matrix                      {NY, NX}; // matrix is rows & columns, array is width & length!!
    std::mt19937 rng                            {Seed()};
    SpinMode spin_mode                          {SpinMode::FullSpin};
    ControlMode control_mode                    {ControlMode::Automatic};
    WolffFiniteStateMachine finite_state_machine{control_mode, spin_mode};
    ImGuiIO& io                                 {PhysGui::GetIO()};
    float temp                                  {3.5f};
    bool has_min_temp                           {true};
    bool should_thermalize_cluster{};
    float latest_temperature{};

public:
    WolffSimulation()
    {
        PhysRunner::LoadFontTTF("fonts/segoeui.ttf");
        for (size_t i = 0; i < 10'000; i++)
        {
            finite_state_machine.runAlgorithm(spin_matrix, rng, temp);
        }
        spin_mode       = SpinMode::QuadrupleSpin;
        control_mode    = ControlMode::Automatic;
        temp            = 1.6f;
    }
    void Update() override
    {
        PhysGui::PhysWindow::Create("window_tag")
        .SetFlags(ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings)
        .SetFullScreen(true) 
        .Show([&]
        {
            //////////////////////////////////////////////////
            PhysGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            PhysGui::SameLine();
            PhysGui::Checkbox("Low temperature cutoff for Auto-Fullcluster mode (Tc = 2.3)", &has_min_temp);
            if (temp < 2.3f && spin_mode==SpinMode::FullSpin && control_mode == ControlMode::Automatic && has_min_temp)
            {
                temp = 2.3f;
            }


            //////////////////////////////////////////////////
            PhysGui::SeparatorText("Control Panel");
        
            PhysGui::Table::Create("MyTable", 4)
            .SetFlags(ImGuiTableFlags_BordersInnerV)
            .Show([this]
            {
                PhysGui::Table::Column([this]
                {
                    PhysGui::SliderFloat("temp", &temp, MIN_TEMP, MAX_TEMP);  
                });
                PhysGui::Table::Column([this]{
                    PhysGui::Group([this]{
                        PhysGui::Text("Control:");
                        PhysGui::SameLine();
                        PhysGui::EnumRadioButton("Auto", control_mode, ControlMode::Automatic);
                        PhysGui::SameLine();
                        PhysGui::EnumRadioButton("Manual", control_mode, ControlMode::Manual);
                        PhysGui::SameLine();
                    });
                });
                PhysGui::SameLine();
                PhysGui::Table::Column([this]{
                    PhysGui::Group([this]{
                        PhysGui::Text("Spins/Frame:");
                        PhysGui::SameLine();
                        PhysGui::EnumRadioButton("1", spin_mode, SpinMode::SingleSpin);
                        PhysGui::SameLine();
                        PhysGui::EnumRadioButton("2", spin_mode, SpinMode::DoubleSpin);
                        PhysGui::SameLine();
                        PhysGui::EnumRadioButton("4", spin_mode, SpinMode::QuadrupleSpin);
                        PhysGui::SameLine();
                        PhysGui::EnumRadioButton("∞", spin_mode,  SpinMode::FullSpin);
                        PhysGui::SameLine();
                    });
                });
                PhysGui::SameLine();
                PhysGui::Table::Column([this]
                {
                    PhysGui::Text("Status:");
                    PhysGui::SameLine();
                    
                    if (finite_state_machine.isLeavingCurrentState())
                    {
                        PhysGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "WAIT...");
                        finite_state_machine.blockSwitches(control_mode, spin_mode);
                        PhysGui::SameLine();

                        if (PhysGui::Button("or thermalize cluster"))
                        {
                            should_thermalize_cluster = true;
                            latest_temperature        = temp;
                            temp                      = MAX_TEMP;
                        }
                        PhysGui::SameLine();
                    }
                    else
                    {
                        PhysGui::TextColored(ImVec4(0.0f, 1.0f, 0.0f, 1.0f), "OK");
                    }

                    if (should_thermalize_cluster && !finite_state_machine.isLeavingCurrentState())
                    {
                        temp                      = latest_temperature;
                        should_thermalize_cluster = false;
                    }
                });
            });
 
            //////////////////////////////////////////////////
            PhysGui::SeparatorText("Simulation");
 
            auto mouse       = io.MousePos;
            auto spin_color  = SPIN_UP_COLOR;
            ImVec2 avail     = PhysGui::GetContentRegionAvail();
            auto p           = PhysGui::GetCursorScreenPos();

            spin_matrix.seed.resetSeed();

            float x_start = p.x + (avail.x - NX*SQR_SIZE )*0.5f;
            float y_start = p.y + (avail.y - NY*SQR_SIZE )*0.5f;
            for (int x = 0; x<NX; x++)
            {
                for (int y = 0; y < NY; y++)
                {
                    float x_prime = x_start + (float)x*SQR_SIZE;
                    float y_prime = y_start + (float)y*SQR_SIZE;
                    if (spin_matrix.at(x, y) == MyGuiArray::spinUp())
                    {
                        spin_color = SPIN_UP_COLOR;
                    }
                    else if (spin_matrix.at(x, y) == MyGuiArray::spinDown())
                    {
                        spin_color  = SPIN_DOWN_COLOR;
                    }
                    if (mouse.x >= x_prime && mouse.x < x_prime + SQR_SIZE)
                    {
                        if (mouse.y >= y_prime && mouse.y < y_prime + SQR_SIZE)
                        {
                            spin_color = MOUSE_COLOR;
                            if (io.MouseClicked[0])
                            {
                                spin_matrix.seed.SelectSeed(x, y);
                            }
                        }
                    }
                    checkboard_img.Paint(x,y, spin_color);
                }
            } 
            
            checkboard_texture.Update(checkboard_img);
            auto p_min = ImVec2{x_start, y_start};
            auto p_max = ImVec2{p_min.x + ZOOM_RATIO*checkboard_texture.width, p_min.y + ZOOM_RATIO*checkboard_texture.height};
            
            checkboard_texture.Draw(p_min, p_max);
 
            finite_state_machine.handleEvents(control_mode, spin_mode);
            finite_state_machine.transitionState();
            finite_state_machine.runAlgorithm(spin_matrix, rng, temp);
        });
    }
};

 


using PhysRunner::CrossPlatformRunner;

int main(int argc, char** argv)
{
    constexpr PhysRunner::Options options =
    {
        .title  = "Wolff Simulation",
        .width  = 1280,
        .height = 720,
    };
 

    CrossPlatformRunner::RunCrossPlatform(options, []()
    {
        return std::make_unique<WolffSimulation>();
    });

    return 0;
}
   
   
    