/*
 * graph.h
 *
 * Description:
 *  This file defines the graph structure used in the Rift Builder project.
 * 
 */

#ifndef RIFT_BUILDER_GRAPH_H
#define RIFT_BUILDER_GRAPH_H

#include "module.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct node_t {
    module_t*       module;
    struct node_t** deps;
    size_t          dep_count;
    bool            visited;
} node_t;

typedef struct graph_t {
    node_t**    nodes;
    size_t      node_count;
} graph_t;

graph_t* graph_gen_graph( module_t* root );
void free_graph( graph_t* g );

#endif /* RIFT_BUILDER_GRAPH_H */