#include "interface_gui_array_2d.hpp"
#include "wolff_finite_state_machine.hpp"
#include "raylib_array_2d/raylib_array_2d.hpp"
#include <random>
#include <functional>
#include "RayGuiWrapper.hpp"
#include <chrono>


constexpr float INVERSE_TEMP_CUTOFF {10E6f};

// Finite State Machine:

// The Base class for the states is "WolffState". We create two child classes "ManualState" & "AutomaticState"
// We then create the base WolffAlgorithm base class and derive two child classes: "SingleSpinAlgorithm" & "FullClusterAlgorithm"
// We use SingleSpinAlgorithm & FullClusterAlgorithm instances as composition and inherit from the classes "ManualState" & "AutomaticState"
// to create "ManualStateSingleSpin", "FullManualClusterCreator", "SingleSpinAutomaticClusterCreator", "FullAutomaticClusterCreator" 


using raylib_array_2d::RayArray2d;   
    
#include <functional>
namespace ray
{  
    void Display(std::function<void()> ui)
    {
        ray::BeginDrawing();
        ui();
        ray::EndDrawing();
    }
}

int main(void)
{
    
    // spin graphic characteristics
    raylib_array_2d::setSpinUpColor(ray::BLUE);
    raylib_array_2d::setSpinDownColor(ray::PURPLE);
    raylib_array_2d::setXoffset(50);
    raylib_array_2d::setYoffset(75);
    raylib_array_2d::setSpinRectWidth(5);
    raylib_array_2d::setSpinRectHeight(5);


    // initiliaze RNG:
    auto seed = static_cast<uint32_t>(std::chrono::system_clock::now().time_since_epoch().count());
    std::mt19937 rng{seed};

    // initiliaze spin matrix
    const int64_t rows{140}; 
    const int64_t cols{200}; 

    // RaySpin2D SpinMatrix{rows, cols};
    RayArray2d SpinMatrix{rows, cols};
    SpinMatrix.randomizeSpins(rng);


    // init window
    uint64_t win_height = rows*Y_SPIN_STEP + 2*Y_OFFSET;
    uint64_t win_width  = cols* X_SPIN_STEP + 2*X_OFFSET;
    ray::InitWindow(win_width, win_height, "Wolff Algorithm");


    // Set Style
    ray::GuiSetStyle(ray::DEFAULT, ray::TEXT_SIZE, 20);


    // Mode selector
    ControlMode controlmode{ControlMode::Automatic};
    float x_slider1        {3*(float)win_width/6.f};
    float y_slider         {(float)raylib_array_2d::getYoffset()/3.f};
    float width_slider     {(float)win_width/7.f};   
    float height_slider    {(float)raylib_array_2d::getYoffset()/3.f};
    
    RayToggleSlider controlModeToggle(x_slider1, y_slider, width_slider, height_slider);
    controlModeToggle.setSwitchName("Auto;Manual");


    // Spin Mode selector
    SpinMode spin_mode  {SpinMode::SingleSpin};
    float x_slider2     {4*(float)win_width/6.f}; 
    RayToggleSlider spinModeToggle{x_slider2, y_slider, width_slider, height_slider};
    spinModeToggle.setSwitchName("Single;Full");
    

    // temperature slidebar
    float width_slidebar    {(float)win_width/4.f};   
    
    RaySliderBar temperatureSlider {(float)raylib_array_2d::getXoffset(), y_slider, width_slidebar, height_slider};
    temperatureSlider.setLeftText("Temperature");
    temperatureSlider.setSlideLimits(0.01f, 5.0f);


    // Text
    float x_wait =  5*(float)win_width/6;
    float y_wait =  y_slider;

    RayText textWait{x_wait, y_wait, ray::BLACK};

    
    // initialize values
    float temperature    = 0.5; //2.77;
    size_t frame_counter = 0;

    WolffFiniteStateMachine newMachine{ControlMode::Manual, SpinMode::SingleSpin};
    while (!ray::WindowShouldClose())
    {
        newMachine.handleEvents(controlmode, spin_mode);
        newMachine.transitionState();
        newMachine.runAlgorithm(SpinMatrix, rng, temperature);
        newMachine.handleExtremeTemperature(temperature, 2.3f);
 
        // -- <draw> -- //
        // ray::BeginDrawing();
        ray::Display([&]
        {
            ray::ClearBackground(ray::RAYWHITE);
            
            SpinMatrix.drawAll();
            SpinMatrix.highlightSelectedSpin();
            temperatureSlider.activateAndDraw(temperature);
            controlModeToggle.activateAndDrawEnum(controlmode);
            spinModeToggle.activateAndDrawEnum(spin_mode);

            if(newMachine.isLeavingCurrentState())
            {
                textWait.writeAnddraw("Wait...");
                newMachine.blockSwitches(controlmode, spin_mode);
            }
            ray::DrawFPS(raylib_array_2d::getXoffset(), win_height - raylib_array_2d::getYoffset()/2);
        });
        // ray::EndDrawing();
        // -- </draw> -- //

        frame_counter++;
    }
    ray::CloseWindow();
    return 0;
}
