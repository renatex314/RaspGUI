#ifndef _EVENT_H
#define _EVENT_H

namespace uikit
{
    namespace event
    {
        namespace mouse
        {
            enum MouseEventType
            {
                MOUSE_DOWN,
                MOUSE_UP,
                MOUSE_MOVE,
                MOUSE_WHEEL
            };
            enum MouseButton
            {
                MOUSE_BUTTON_LEFT,
                MOUSE_BUTTON_MIDDLE,
                MOUSE_BUTTON_RIGHT
            };
            struct MouseEvent
            {
                int x;
                int y;
                int wheel_x;
                int wheel_y;
                MouseEventType type;
                MouseButton button;
            };
        };

        namespace keyboard
        {
            enum KeyEventType
            {
                KEY_DOWN,
                KEY_UP
            };
            struct KeyEvent
            {
                KeyEventType type;
                int sdl_key_code;
            };
        }
    }
}

#endif