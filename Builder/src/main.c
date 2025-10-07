#include "module.h"
#include "graph.h"
#include "order.h"
#include "command.h"
#include "build.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main( int argc, char** argv )
{
    if ( argc < 2 ) {
        fprintf( stderr, "Usage: %s <module_file>\n", argv[0] );
        return 1;
    }
    
    char path[256];
    snprintf(path, sizeof(path), "./%s/module.build", argv[1]);
    printf( "Loading module from file: %s\n", path );
    module_t* module = load_module_definition( path );
    if ( !module ) { fprintf( stderr, "Failed to load module from file: %s\n", path ); return 1; }

    /* Print module information */
    printf( "Module Name: %s\n", module->name );
    printf( "Module Type: %s\n", 
        module->type == MODULE_TYPE_SHAREDLIB ? "Shared Library" :
        module->type == MODULE_TYPE_STATICLIB ? "Static Library" :
        module->type == MODULE_TYPE_EXECUTABLE ? "Executable" : "Unknown" );
    printf( "Module Version: %d.%d.%d\n", (module->version >> 16) & 0xFF, (module->version >> 8) & 0xFF, module->version & 0xFF );
    for ( uint32_t i = 0; i < module->source_files->count; ++i ) {
        printf( "Source File: %s\n", module->source_files->items[i] );
    }
    for ( uint32_t i = 0; i < module->public_include_paths->count; ++i ) {
        printf( "Public Include Path: %s\n", module->public_include_paths->items[i] );
    }
    for ( uint32_t i = 0; i < module->dependencies->count; ++i ) {
        printf( "Dependency: %s\n", module->dependencies->items[i] );
    }
    for ( uint32_t i = 0; i < module->defines->count; ++i ) {
        printf( "Define: %s\n", module->defines->items[i] );
    }
    printf( "Export Flag: %s\n", module->export_flag ? "true" : "false" );

    /* Generate and print the dependency graph */
    printf( "Generating dependency graph...\n" );

    graph_t* g = graph_gen_graph( module );
    printf( "Graph has %zu nodes.\n", g->node_count );
    for ( size_t i = 0; i < g->node_count; i++ ) {
        node_t* n = g->nodes[i];
        printf( "Node: %s, Dependencies: %zu\n", n->module->name, n->dep_count );
        for ( size_t j = 0; j < n->dep_count; j++ ) {
            printf( "  - %s\n", n->deps[j]->module->name );
        }
    }

    build_order_t* order = build_order( g );
    printf( "Build order has %u modules:\n", order->count );
    for ( uint32_t i = 0; i < order->count; ++i ) {
        printf( "%u: %s\n", i + 1, order->modules[i]->name );
    }
    
    commands_t* cmds;
    if ( argv[2] && strcmp( argv[2], "Debug" ) == 0 ) {
        cmds = build_gen_commands( order, BUILD_TYPE_DEBUG );
    } else if ( argv[2] && strcmp( argv[2], "Release" ) == 0 ) {
        cmds = build_gen_commands( order, BUILD_TYPE_RELEASE );
    } else {
        fprintf( stderr, "Usage: %s <module_file> <Debug|Release>\n", argv[0] );
        return 1;
    }

    bool success = build_build( cmds );
    if ( success ) {
        printf( "Build completed successfully.\n" );
    } else {
        printf( "Build failed.\n" );
    }

    printf( "Freeing build order...\n" );
    build_order_free( order );
    printf( "Freeing graph...\n" );
    free_graph( g );

    return 0;
}