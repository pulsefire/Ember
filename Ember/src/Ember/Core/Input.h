#ifndef EMBER_INPUT
#define EMBER_INPUT


#include "Ember/Core/Core.h"
#include "Ember/Core/EmberApp.h"


namespace Ember
{
    class EMBER_API Input
    {
    public:
        static inline int IsKeyPressed(int keycode)
        {
            return m_Instance->IsKeyPressedImpl(keycode);
        }

        static inline int IsMouseButtonPressed(int button)
        {
            return m_Instance->IsMouseButtonPressedImpl(button);
        } 

        static inline std::pair<double,double> GetMousePos()
        {
            return m_Instance->GetMousePosImpl();
        } 

        static inline double GetMouseX()
        {
            return m_Instance->GetMouseXImpl();
        }

        static inline double GetMouseY()
        {
            return m_Instance->GetMouseYImpl();
        }

    protected:
        int IsKeyPressedImpl(int keycode);
        int IsMouseButtonPressedImpl(int button);

        std::pair<double,double> GetMousePosImpl();
        double GetMouseXImpl();
        double GetMouseYImpl();

    private:
        static Input* m_Instance;
    };
};






#endif