#pragma once
#include "Event.h"

namespace Rift {
    class KeyEvent : public Event {
    public:
        inline int GetKeyCode() const { return key; }

        EVENT_CLASS_CATEGORY (EventCategoryKeyboard
        |
        EventCategoryInput
        )

    protected:
        KeyEvent(int keycode) : key(keycode) {
        }

        int key;
    };

    class KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), repeatCount(repeatCount) {
        }

        inline int GetRepeatCount() const { return repeatCount; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << key << " (" << repeatCount << " repeats)";
            return ss.str();
        }

        EVENT_CLASS_TYPE (KeyPressed)

    private:
        int repeatCount;
    };

    class KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keycode) : KeyEvent(keycode) {
        }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << keycode;
            return ss.str();
        }

        EVENT_CLASS_TYPE (KeyReleased)
    }
}