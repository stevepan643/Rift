/*
 * WindowEvents.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#ifndef RIFT_WINDOWEVENTS_H
#define RIFT_WINDOWEVENTS_H

#include "Event/Event.h"
#include "Window.h"

namespace Rift {
    class WindowErrorEvent : public Event {
    public:
        explicit WindowErrorEvent( const char *description ) : description( description ) {}

        const char *GetDiscription() const { return description; }

    private:
        const char *description;
    };

    class WindowResizeEvent : public Event {
    public:
        WindowResizeEvent( uint32_t width, uint32_t height ) : Width( width ), Height( height ) {};

        uint32_t GetWidth() const { return Width; }
        uint32_t GetHeight() const { return Height; }

    private:
        uint32_t Width, Height;
    };

    class WindowCloseEvent : public Event {};
} // namespace Rift

#endif // RIFT_WINDOWEVENTS_H
