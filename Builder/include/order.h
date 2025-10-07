/*
 * order.h
 *
 * Description:
 *  This file defines the order structure used in the Rift Builder project.
 */

#ifndef RIFT_BUILDER_ORDER_H
#define RIFT_BUILDER_ORDER_H

#include "module.h"
#include "graph.h"

#include <stdint.h>

typedef struct build_order_t {
    module_t** modules;
    uint32_t    count;
} build_order_t;

build_order_t* build_order( graph_t* graph );

void build_order_free( build_order_t* order );

#endif /* RIFT_BUILDER_ORDER_H */