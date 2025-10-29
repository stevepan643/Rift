/*
 * Layer.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#ifndef RIFT_LAYER_H
#define RIFT_LAYER_H

namespace Rift {
    class Layer {
    public:
        Layer( const std::string &name = "Layer" );
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate( float delta ) {}
        virtual void OnImGuiRender() {}

        const std::string &GetName() const { return Name; }

    protected:
        std::string Name;
    };
} // namespace Rift

#endif // RIFT_LAYER_H
