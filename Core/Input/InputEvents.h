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
} // Rift

#endif //RIFT_INPUTEVENTS_H
