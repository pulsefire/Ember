#include "Core/Core.h"
#include "Gui/GuiLayer.h"

namespace Ember
{

    GuiLayer::GuiLayer()
        : m_Time(0.0f), Ember::Layer("ImGuiLayer")
    {

    }

    GuiLayer::~GuiLayer()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui::DestroyContext();
    }

    void GuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();

        // this->cambria = io.Fonts->AddFontFromFileTTF("C:\\CDEV\\Ember\\Ember\\dependencies\\imgui\\BubbbleGum.otf", 14.0f, NULL, NULL);
        this->cambria = io.Fonts->AddFontFromFileTTF("../../../Ember/res/fonts/BubbbleGum.otf", 14.0f, NULL, NULL);

        ER_CORE_ASSERT((this->cambria != nullptr), "Font not loaded!");

        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void GuiLayer::OnDetach()
    {

    }

    void GuiLayer::OnUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();

        // Access application/window data like singleton
        EmberApp& app = EmberApp::Get();
        io.DisplaySize = ImVec2(app.m_Window->WinData.width, app.m_Window->WinData.height);

        float time = (float)glfwGetTime();
        io.DeltaTime = (m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f));
        m_Time = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        // bool show_another_window = true;
        // ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
        // ImGui::Text("Hello from another window!");
        // if (ImGui::Button("Close Me"))
        //     show_another_window = false;
        // ImGui::End();

        static bool show_demo_window = true;
        ImGui::ShowDemoWindow(&show_demo_window);

        ImGui::Render();
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void GuiLayer::OnEvent(Event& event)
    {
        // ER_CORE_TRC(event);
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MousePressEvent>(std::bind(&GuiLayer::OnMousePressEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseReleaseEvent>(std::bind(&GuiLayer::OnMouseReleaseEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseMoveEvent>(std::bind(&GuiLayer::OnMouseMoveEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseScrollEvent>(std::bind(&GuiLayer::OnMouseScrollEvent, this, std::placeholders::_1));

        dispatcher.Dispatch<KeyPressEvent>(std::bind(&GuiLayer::OnKeyPressEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyReleaseEvent>(std::bind(&GuiLayer::OnKeyReleaseEvent, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyTypeEvent>(std::bind(&GuiLayer::OnKeyTypeEvent, this, std::placeholders::_1));

        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&GuiLayer::OnWindowResizeEvent, this, std::placeholders::_1));
    }

    bool GuiLayer::OnMousePressEvent(MousePressEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.GetMouseButton()] = true;

        return false;
    }

    bool GuiLayer::OnMouseReleaseEvent(MouseReleaseEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[event.GetMouseButton()] = false;

        return false;
    }

    bool GuiLayer::OnMouseMoveEvent(MouseMoveEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos.x = event.GetX();
        io.MousePos.y = event.GetY();
        
        return false;
    }

    bool GuiLayer::OnMouseScrollEvent(MouseScrollEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += (float)event.GetOffsetX();
        io.MouseWheel += (float)event.GetOffsetY();

        return false;
    }

    bool GuiLayer::OnKeyPressEvent(KeyPressEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.GetKeyCode()] = true;

        // Modifiers are not reliable across systems
        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];

        io.KeySuper = false;
    }

    bool GuiLayer::OnKeyReleaseEvent(KeyReleaseEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[event.GetKeyCode()] = false;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];

        io.KeySuper = false;
    }

    bool GuiLayer::OnKeyTypeEvent(KeyTypeEvent& event)  
    {
        ImGuiIO& io = ImGui::GetIO();
        io.AddInputCharacter((char)event.GetKeyCode());
        return false;
    }

    bool GuiLayer::OnWindowResizeEvent(WindowResizeEvent& event)
    {
        ImGuiIO& io = ImGui::GetIO();
        return false;
    }

};

