/*
 * LayerStack.cpp
 *
 * Copyright (c) 2025 Steve Pan
 * SPDX-License-Identifier: MIT
 *
 * This file is part of Rift.
 * Created at 10/28/2025
 */

#include "LayerStack.h"

namespace Rift {
    LayerStack::~LayerStack() {
        for ( Layer *layer : layers ) {
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::PushLayer( Layer *layer ) {
        layers.emplace( layers.begin() + layerInsertIndex, layer );
        layerInsertIndex++;
    }

    void LayerStack::PushOverlay( Layer *overlay ) { layers.emplace_back( overlay ); }

    void LayerStack::PopLayer( Layer *layer ) {
        auto it = std::find( layers.begin(), layers.begin() + layerInsertIndex, layer );
        if ( it != layers.begin() + layerInsertIndex ) {
            layer->OnDetach();
            layers.erase( it );
            layerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay( Layer *overlay ) {
        auto it = std::find( layers.begin() + layerInsertIndex, layers.end(), overlay );
        if ( it != layers.end() ) {
            overlay->OnDetach();
            layers.erase( it );
        }
    }

} // namespace Rift
