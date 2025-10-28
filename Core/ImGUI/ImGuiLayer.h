/* 
 * ImGuiLayer.h
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 * 
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#ifndef RIFT_IMGUILAYER_H
#define RIFT_IMGUILAYER_H

#include "Layer/Layer.h"

namespace Rift {
    class ImGuiLayer : public Layer {
    public:
        ImGuiLayer();
        ~ImGuiLayer() override;

        void OnAttach() override;

        void OnDetach() override;

        void OnUpdate(float delta) override;
    private:
        float time = 0.0f;
    };
} // Rift

#endif //RIFT_IMGUILAYER_H