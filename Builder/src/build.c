/*
 * build.c - Rift Builder build execution
 */

#include "build.h"

#include <stdlib.h>
#include <stdio.h>

bool build_build(commands_t* cmds) {
    if (!cmds || !cmds->list) return false;

    for (uint32_t i = 0; i < cmds->count; ++i) {
        command_t* c = &cmds->list[i];
        printf("Running build command for %s:\n  %s\n", c->module_name, c->cmd);

        int ret = system(c->cmd);  // 执行命令
        if (ret != 0) {
            printf("Error: build failed for %s (exit code %d)\n", c->module_name, ret);
            return false;
        }
    }
    return true;
}