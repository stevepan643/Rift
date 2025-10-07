/*
 * build.c - Rift Builder build execution
 */

#include "build.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

bool build_build(commands_t* cmds) {
    if (!cmds || !cmds->list) return false;

    for (uint32_t i = 0; i < cmds->count; ++i) {
        command_t* c = &cmds->list[i];

        // 进度百分比
        int progress = (int)((i * 100) / cmds->count);
        int bars = progress / 2; // 50 格子

        // ANSI 动态刷新
        printf("\r[");
        for (int j = 0; j < 50; ++j)
            putchar(j < bars ? '#' : ' ');
        printf("] %3d%% | Running: %s\n", progress, c->module_name);
        fflush(stdout);

        // 执行命令
        int ret = system(c->cmd);
        if (ret != 0) {
            printf("\nBuild failed for %s (exit code %d)\n", c->module_name, ret);
            return false;
        }
    }

    // 最终 100% 完成
    printf("\r[##################################################] 100%% | Build complete! \n");
    return true;
}
