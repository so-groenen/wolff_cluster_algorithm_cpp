#ifndef IMGUI_EWRAPPER_HPP
#define IMGUI_EWRAPPER_HPP

#include <imgui.h>
#include <functional>
#include <concepts>



namespace PhysGui
{
    using namespace ImGui; // reimport into the physgui namepace

    template<std::invocable F>
    bool MenuBar(F ui)
    {
        bool result {};
        if(result = ImGui::BeginMenuBar(); result)
        {
            ui();
            ImGui::EndMenuBar();
        }
        return result;
    }
    class ItemWidth
    {
        float m_region_avail_percent{1.};
        ItemWidth(float region_avail_percent)
           :  m_region_avail_percent{region_avail_percent}
        {
        }
    public:
        static ItemWidth Create(float region_avail_percent)
        {
            return {region_avail_percent};
        }
        template<std::invocable F>
        void Show(F ui)
        {
            ImGui::PushItemWidth(ImGui::GetContentRegionAvail().x * m_region_avail_percent);
            ui();
            ImGui::PopItemWidth();
        }
    };

    template<std::invocable F>
    void StyleColor(ImGuiCol idx, const ImVec4& col, F ui)
    {
        ImGui::PushStyleColor(idx, col);
        ui();
        ImGui::PopStyleColor();
    }
    template<std::invocable F>
    void Group(F ui)
    {
        ImGui::BeginGroup();
        ui();
        ImGui::EndGroup();
    }

    template<std::invocable Ui>
    bool Menu(const char* label, Ui ui)
    {
        bool result {};
        if(result = ImGui::BeginMenu(label); result)
        {
            ui();
            ImGui::EndMenu();
        }
        return result;
    }

    class PhysWindow
    {
        const char* m_name{};
        bool* m_open{};
        bool m_isFullScreen{};
        ImGuiWindowFlags m_flags{};
        PhysWindow(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0)
            : m_name{name}, m_open{p_open}, m_flags{flags}
        {

        }
    public:
        static PhysWindow Create(const char* name, bool* p_open = NULL, ImGuiWindowFlags flags = 0)
        {
            return {name, p_open, flags};
        }
        PhysWindow& SetFullScreen(bool v)
        {
            m_isFullScreen = v;
            if(m_isFullScreen && !(ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable))
            {
                ImGui::SetNextWindowPos(ImVec2{});
                ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
            }
            return *this;
        }
        PhysWindow& SetFlags(ImGuiWindowFlags flag)
        {
            m_flags = flag;
            return *this;
        }
        template <std::invocable Ui>
        void Show(Ui ui)
        {
            ImGui::Begin(m_name, m_open, m_flags);
            ui();
            ImGui::End();   
        }
    };


    // template <std::invocable T>
    class Table
    {
        const char* m_str_id{};
        int m_columns{};
        ImGuiTableFlags m_flags{};
        ImVec2 m_outer_size{};
        float m_inner_width{};
        // size_t m_columnSetupStartIndex{g_currentColumnIndex};
        // size_t m_ColumnSetupCounter{};
        Table(const char* str_id, int columns, ImGuiTableFlags flags = 0, ImVec2 outer_size = ImVec2(0.0f, 0.0f), float inner_width = 0.0f)
            : m_str_id{str_id}, m_columns{columns}, m_flags{flags}, m_outer_size{outer_size}, m_inner_width{inner_width}
        {

        }
    public:
        template <std::invocable Ui>
        static void Column(Ui ui)
        {
            ImGui::TableNextColumn();
            ui();
        }
        template <std::invocable Ui>
        static void Row(Ui ui)
        {
            ImGui::TableNextRow();
            ui();
        }
        static Table Create(const char* str_id, int columns, ImGuiTableFlags flags = 0, const ImVec2& outer_size = ImVec2(0.0f, 0.0f), float inner_width = 0.0f)
        {
            return {str_id, columns};
        }
        Table& SetFlags(ImGuiTableFlags flags)
        {
            m_flags = flags;
            return *this;
        }
        Table& OuterSize(ImVec2 outer_size)
        {
            m_outer_size = outer_size;
            return *this;
        }
        Table& InnerWidth(float inner_width)
        {
            m_inner_width = inner_width;
            return *this;
        }
        // Table& SetColumn(const char* label, ImGuiTableColumnFlags flags = 0, float init_width_or_weight = 0.0f, ImGuiID user_id = 0)
        // {
        //     IM_ASSERT(g_currentColumnIndex < MAX_COLUMN_SETUPS && "Max amount of cols used\n");

        //     g_columnSetups[g_currentColumnIndex++] = (ColumnSetup)
        //     {
        //         .label = label,
        //         .flags = flags,
        //         .init_width_or_weight = init_width_or_weight,
        //         .user_id = user_id,  
        //     };
        //     m_ColumnSetupCounter++;
        //     return *this;
        // }
        // template <std::invocable T>
        // Table& SetupColumns(T setup)
        // {
        //     m_setup_callback = setup;
        //     return *this;
        // }

        template <std::invocable Ui>
        void Show(Ui ui) const
        {
            if(ImGui::BeginTable(m_str_id, m_columns, m_flags, m_outer_size, m_inner_width))
            {
                // if (m_ColumnSetupCounter) //if we added some setups
                // {
                //     for (size_t i = m_columnSetupStartIndex; i < m_columnSetupStartIndex + m_ColumnSetupCounter; i++)
                //     {
                //         ImGui::TableSetupColumn(g_columnSetups[i].label, g_columnSetups[i].flags, g_columnSetups[i].init_width_or_weight, g_columnSetups[i].user_id);
                //     }
                // }
                ui();
                ImGui::EndTable();
            }
        }
        // ~Table()
        // {
        //     for(size_t i{}; i < m_ColumnSetupCounter; i++)
        //     {
        //         g_currentColumnIndex--;
        //     }
        // }   
    };


  
    template<typename T>
    void EnumRadioButton(const char* label, T& value, T v_button) requires std::is_enum_v<T>
    {
        int int_value    {static_cast<int>(value)};
        RadioButton(label, &int_value, static_cast<int>(v_button));
        value = static_cast<T>(int_value);
    }

    class Node
    {
        bool m_clicked{false};
        const char* m_label;
        Node(const char* label) 
            : m_label{label}
        {
        }
        Node() = default;
    public:
        static Node Create(const char* label)
        {
            return {label};
        }
        template<std::invocable Ui>
        bool Clicked(Ui ui)
        {
            if (ImGui::TreeNode(m_label))
            {
                ui();
                ImGui::TreePop();
                return true;
            }
            return false;
        }
    };

    class Child
    {
        const char* m_str_id{};
        const ImVec2& m_size_arg;
        ImGuiChildFlags m_child_flags{};
        ImGuiWindowFlags m_window_flags{};
        Child(const char* str_id, const ImVec2& size_arg = ImVec2(0, 0))
            : m_str_id{str_id}, m_size_arg{size_arg}
        {
        }
    public:
        static Child Create(const char* str_id, const ImVec2& size_arg = ImVec2(0, 0))
        {
            return {str_id, size_arg};
        }
        Child& ImGuiWindowFlags(ImGuiWindowFlags window_flags)
        {
            m_window_flags = window_flags;
            return *this;
        }
        Child& ImGuiChildFlags(ImGuiChildFlags child_flags)
        {
            m_child_flags = child_flags;
            return *this;
        }
        Child& Borders(bool val)
        {
            if (val) 
                m_child_flags |= ImGuiChildFlags_Borders;
            return *this;
        }
        Child& ResizeX(bool val)
        {
            if (val)
                m_child_flags |= ImGuiChildFlags_ResizeX;
            return *this;
        }
        template<std::invocable Ui>
        bool Show(Ui ui)
        {
            bool result {ImGui::BeginChild(m_str_id, m_size_arg, m_child_flags, m_window_flags)};
            if (result)
            {
                ui();
            }            
            ImGui::EndChild();
            return result;
        }
    };
}

#endif