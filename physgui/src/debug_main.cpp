#include "phys_gui/phys_runner.hpp" 
#include "phys_gui/phys_gui.hpp" 
#include <iostream>
#include <print>

// using PhysRunner::CrossPlatformRunner;
using namespace PhysRunner;

// For web prefer using dynamic memory! Use IphysGuiApp interface + smart pointers!

class MyPhysicsTemplate : public PhysRunner::IPhysGuiApp
{
    bool show_demo_window{};
    float value{};
    uint32_t counter{};

public:
    MyPhysicsTemplate()
    {
        ImGui::GetIO().Fonts->AddFontFromFileTTF("fonts/segoeui.ttf");
    }
    void Update() override
    {
        PhysGui::PhysWindow::Create("HelloWorld")
        .SetFlags(ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoSavedSettings)
        .SetFullScreen(true) 
        .Show([&]
        {
            PhysGui::Text("This is some useful text.");                
            PhysGui::Checkbox("Demo Window", &show_demo_window);      
            PhysGui::SliderFloat("float", &value, 0.0f, 1.0f);             

            if (PhysGui::Button("Button"))                           
                counter++;
            PhysGui::SameLine();
            PhysGui::Text("counter = %d", counter);

            // if (PhysGui::Button("Close me & clean up in a smart way!"))
            //     CrossPlatformRunner::Close();
            
            

            PhysGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
            PhysGui::Separator();

   
            PhysGui::Table::Create("MyTable", 2)
            .SetFlags(ImGuiTableFlags_BordersInnerV | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Resizable)
            .Show([]
            {
                PhysGui::TableSetupColumn("col 1", ImGuiTableColumnFlags_WidthFixed);
                PhysGui::TableSetupColumn("col 2", ImGuiTableColumnFlags_WidthStretch);
                
                // First col:
                PhysGui::Table::Column([]
                {
                    PhysGui::Text("Blabla");
                    PhysGui::Text("Blabla");
                    PhysGui::Text("Blabla");
                    struct Funcs
                    {
                        static float Sin(void*, int i) { return sinf(i * 0.1f); }
                        static float Cos(void*, int i) { return cosf(i * 0.1f); }
                    };
                    static int func_type = 0, display_count = 70;
                    ImGui::SeparatorText("Functions");
                    ImGui::SetNextItemWidth(ImGui::GetFontSize() * 8);
                    ImGui::Combo("func", &func_type, "Sin\0Saw\0");
                    float (*func)(void*, int) =   Funcs::Sin;

                    ImVec2 graphSize {0.0f, 80.0f};
                    ImGui::PlotLines("Lines##2", func, NULL, display_count, 0, NULL, -1.0f, 1.0f, graphSize);
                });

                // Second col:
                PhysGui::Table::Column([]
                {
                    PhysGui::Child::Create("Experiment")
                    .Show([]
                    {
                        ImGui::Text("Some text");
                        ImGui::Text("Some text");
                        ImGui::Text("Some text2");
                        ImGui::Separator();

                        ImVec2 p {ImGui::GetCursorScreenPos()};
                        ImVec2 availablee_size = ImGui::GetContentRegionAvail();
    
                        ImVec2 center  {availablee_size.x/2.0f, availablee_size.y/2.0f};
                        float length   {0.7f*availablee_size.x};
                        float width    {availablee_size.y};
                        ImVec2 p_min   {p.x + (center.x-length/2.0f), p.y + (center.y-width/2.0f)} ;
                        ImVec2 p_max   {p_min.x + length, p_min.y + width} ;
                        ImGui::GetWindowDrawList()->AddRectFilled(p_min, p_max, ImColor(255, 20, 20, 255));
                    });
                });
            });
        });


        if (show_demo_window)
        {
            ImGui::ShowDemoWindow();
        }
    }
};

int main(int argc, char** argv)
{
    constexpr PhysRunner::Options options =
    {
        .title = "My Test example!!",
        .width = 1280,
        .height = 720,
    };
    // PhysRunner::CrossPlatformRunner::Setup(options).Run(std::make_unique<MyPhysicsTemplate>());
        // std::println("Invoked!");

    // NativeRunner::RunNative<MyPhysicsTemplate>(options);
    CrossPlatformRunner::RunCrossPlatform(options, []()
    {
        return std::make_unique<MyPhysicsTemplate>();
    });
    // Ordering ensures proper init order: 1) SDL for window & events 2) OpenGL for graphics 3) imgui for UI 4) our app
    
    
    return 0;
}
   
   
    