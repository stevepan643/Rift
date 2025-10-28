/* 
 * Event.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 * 
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#ifndef RIFT_EVENT_H
#define RIFT_EVENT_H

namespace Rift {

    class Event {
    public:
        virtual ~Event() = default;

        bool Handled = false;
    };

    using EventCallbackFn = std::function<void(const Event&)>;

    class EventBus {
    public:
        template<typename T>
        void Subscribe(std::function<void(const T&)> callback) {
            auto& vec = subscribers[typeid(T)];
            vec.push_back([callback](const Event& e){
                callback(static_cast<const T&>(e));
            });
        }

        template<typename T>
        void Publish(const T& event) const {
            auto it = subscribers.find(typeid(T));
            if (it == subscribers.end()) return;

            const auto& callbacks = it->second;
            if (callbacks.empty()) return; // Extra safety, should rarely happen

            // Call all subscribers
            for (const auto& cb : callbacks)
                cb(event);
        }
    private:
        std::unordered_map<std::type_index, std::vector<EventCallbackFn>> subscribers;
    };

    inline Ref<EventBus> SystemEvent = CreateRef<EventBus>();
} // Rift

#endif //RIFT_EVENT_H