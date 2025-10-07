/*
 * graph.h
 *
 * Description:
 *  This file defines the command structure used in the Rift Builder project.
 */

#ifndef RIFT_BUILDER_COMMAND_H
#define RIFT_BUILDER_COMMAND_H

#include "order.h"

#include <stdint.h>

typedef struct command_t {
    char* module_name;
    char* cmd;
} command_t;

typedef struct commands_t {
    command_t* list;
    uint32_t count;
} commands_t;

typedef enum build_type_t {
    BUILD_TYPE_DEBUG,
    BUILD_TYPE_RELEASE
} build_type_t;

commands_t* build_gen_commands( build_order_t* order, build_type_t type );

#endif /* RIFT_BUILDER_COMMAND_H */