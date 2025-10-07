#include "module.h"
#include "graph.h"
#include "order.h"
#include "command.h"
#include "build.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int main(int argc, char** argv)
{
    if (argc < 2) {
        fprintf(stderr, "Usage: Builder <Module1> [Module2 ...] <Debug|Release>\n");
        return 1;
    }

    char* build_type_str = argv[argc - 1];
    build_type_t build_type;
    int last_module_index = argc - 2;

    if (strcmp(build_type_str, "Debug") == 0) {
        build_type = BUILD_TYPE_DEBUG;
    } else if (strcmp(build_type_str, "Release") == 0) {
        build_type = BUILD_TYPE_RELEASE;
    } else {
        fprintf(stderr, "Last argument must be Debug or Release\n");
        return 1;
    }

    int module_count = last_module_index;
    if (module_count <= 0) {
        fprintf(stderr, "Please specify at least one module to build\n");
        return 1;
    }

    module_t** modules = malloc(sizeof(module_t*) * module_count);
    for (int i = 0; i < module_count; i++) {
        char path[256];
        snprintf(path, sizeof(path), "./%s/module.build", argv[i + 1]);
        modules[i] = load_module_definition(path);
        if (!modules[i]) {
            fprintf(stderr, "Failed to load module: %s\n", argv[i + 1]);
            free(modules);
            return 1;
        }
    }

    graph_t* g = graph_gen_graph_multiple(modules, module_count);
    build_order_t* order = build_order(g);

    commands_t* cmds = build_gen_commands(order, build_type);
    bool success = build_build(cmds);

    build_order_free(order);
    free_graph(g);
    free(modules);

    return success ? 0 : 1;
}
