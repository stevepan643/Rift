/*
 * graph.c - Rift Builder module graph
 */

#include "module.h"
#include "graph.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static node_t* graph_find_node( graph_t* g, const char* name ) {
    for ( uint32_t i = 0; i < g->node_count; i++ ) {
        if ( strcmp( g->nodes[i]->module->name, name ) == 0 )
            return g->nodes[i];
    }
    return NULL;
}

static node_t* graph_add_node( graph_t* g, module_t* m ) {
    node_t* n = calloc( 1, sizeof( node_t ) );
    n->module = m;
    g->nodes = realloc( g->nodes, sizeof( *g->nodes ) * ( g->node_count + 1 ) );
    g->nodes[g->node_count++] = n;
    return n;
}

static node_t* graph_build_node( graph_t* g, module_t* m ) {
    node_t* n = graph_find_node( g, m->name );
    if ( n ) return n;

    n = graph_add_node( g, m );
    n->dep_count = m->dependencies->count;
    n->deps = calloc( n->dep_count, sizeof( node_t* ) );

    for ( uint32_t i = 0; i < m->dependencies->count; i++ ) {
        char* dep = m->dependencies->items[i];
        char path[256];
        snprintf(path, sizeof(path), "./%s/module.build", dep);
        module_t* dep_mod = load_module_definition( path );
        node_t* dep_node = graph_build_node( g, dep_mod );
        n->deps[i] = dep_node;
    }
    return n;
}

graph_t* graph_gen_graph_multiple(module_t** modules, size_t module_count) 
{
    graph_t* g = calloc(1, sizeof(graph_t));
    if (!g) return NULL;

    for (size_t i = 0; i < module_count; i++) {
        module_t* m = modules[i];
        if (m) {
            graph_build_node(g, m);  // graph_build_node 内部应处理重复节点
        }
    }

    return g;
}

void free_graph( graph_t* g ) {
    if ( !g ) return;

    for ( size_t i = 0; i < g->node_count; i++ ) {
        node_t* n = g->nodes[i];
        if ( n->module ) free_module( n->module );
        free( n->deps );
        free( n );
    }
    free( g->nodes );
}