/* 
 * InputEvents.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 * 
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#ifndef RIFT_INPUTEVENTS_H
#define RIFT_INPUTEVENTS_H

#include "Event/Event.h"

namespace Rift {
    using MouseCode = uint16_t;
    enum : MouseCode {
        Button0                = 0,
        Button1                = 1,
        Button2                = 2,
        Button3                = 3,
        Button4                = 4,
        Button5                = 5,
        Button6                = 6,
        Button7                = 7,

        ButtonLast             = Button7,
        ButtonLeft             = Button0,
        ButtonRight            = Button1,
        ButtonMiddle           = Button2
    };

    class MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y) : curX(x), curY(y) {
        }

        float GetX() const { return curX; }
        float GetY() const { return curY; }
    private:
        float curX, curY;
    };

    class MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float x, float y) : offsetX(x), offsetY(y) {}

        float GetOffsetX() const { return offsetX; }
        float GetOffsetY() const { return offsetY; }
    private:
        float offsetX, offsetY;
    };

    class MouseButtonEvent : public Event {
    public:
        MouseCode GetMouseButton() const { return button; }
    protected:
        MouseButtonEvent(const MouseCode code) : button(code) {}
        MouseCode button;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(const MouseCode button) : MouseButtonEvent(button) {}
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(const MouseCode button) : MouseButtonEvent(button) {}
    };
} // Rift

#endif //RIFT_INPUTEVENTS_H
