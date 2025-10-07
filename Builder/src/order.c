/*
 * order.c - Determine build order from dependency graph
 */

#include "order.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static void dfs_visit( node_t* node, module_t** list, 
                       uint32_t* index, bool* cycle_detected ) 
{
    if ( node->visited ) return;
    node->visited = true;

    for ( uint32_t i = 0; i < node->dep_count; ++i ) {
        node_t* dep = node->deps[i];
        if ( dep->visited ) continue;
        dfs_visit( dep, list, index, cycle_detected );
    }

    list[ (*index)++ ] = node->module;
}

build_order_t* build_order( graph_t* graph )
{
    build_order_t* order = (build_order_t*) calloc( 1, sizeof(build_order_t) );
    if ( !graph || !graph->nodes || graph->node_count == 0 ) return order;

    order->modules = (module_t**) calloc( graph->node_count, sizeof(module_t*) );
    if ( !order->modules ) return order;

    uint32_t index = 0;
    for ( uint32_t i = 0; i < graph->node_count; ++i )
        graph->nodes[i]->visited = false;

    bool cycle_detected = false;
    for ( uint32_t i = 0; i < graph->node_count; ++i ) {
        node_t* node = graph->nodes[i];
        if ( !node->visited )
            dfs_visit( node, order->modules, &index, &cycle_detected );
    }

    // for ( uint32_t i = 0; i < index / 2; ++i ) {
    //     module_t* tmp = order->modules[i];
    //     order->modules[i] = order->modules[index - i - 1];
    //     order->modules[index - i - 1] = tmp;
    // }

    order->count = index;
    return order;
}

void build_order_free( build_order_t* order )
{
    if ( !order ) return;
    free( order->modules );
    free( order );
}