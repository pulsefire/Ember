#include "Ember/Core/Input.h"


namespace Ember
{

    int Input::IsKeyPressedImpl(int keycode)
    {   
        auto window = EmberApp::Get().GetWindow()->GetNativeWindow();
        int state = glfwGetKey(window, keycode);
        return state >= GLFW_PRESS;
    }

    int Input::IsMouseButtonPressedImpl(int button)
    {
        auto window = EmberApp::Get().GetWindow()->GetNativeWindow();
        int state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<double,double> Input::GetMousePosImpl()
    {
        auto window = EmberApp::Get().GetWindow()->GetNativeWindow();
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        return {xpos, ypos};
    }

    double Input::GetMouseXImpl()
    {
        auto p = GetMousePosImpl();
        return std::get<0>(p);
    }

    double Input::GetMouseYImpl()
    {
        auto p = GetMousePosImpl();
        return std::get<1>(p);
    }





}