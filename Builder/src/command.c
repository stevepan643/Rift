/*
 * command.c - Rift Builder command line interface
 */

#include "command.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static char* str_toupper(const char* s) {
    size_t len = strlen(s);
    char* out = malloc(len + 1);
    for (size_t i = 0; i < len; ++i) out[i] = (char)toupper((unsigned char)s[i]);
    out[len] = '\0';
    return out;
}

// 判断数组中是否已经存在某字符串
static bool str_list_contains(char** list, size_t count, const char* s) {
    for (size_t i = 0; i < count; ++i)
        if (strcmp(list[i], s) == 0) return true;
    return false;
}

commands_t* build_gen_commands(build_order_t* order, build_type_t type) {
    commands_t* cmds = calloc(1, sizeof(commands_t));
    cmds->count = order->count;
    cmds->list = calloc(cmds->count, sizeof(command_t));

    for (uint32_t i = 0; i < order->count; ++i) {
        module_t* m = order->modules[i];
        size_t buf_size = 4096;
        char* cmd = calloc(1, buf_size);
        char lib_suffix[16] = "";
        bool is_shared = (m->type == MODULE_TYPE_SHAREDLIB);

        if (is_shared) {
#ifdef _WIN32
            snprintf(lib_suffix, sizeof(lib_suffix), ".dll");
#elif __APPLE__
            snprintf(lib_suffix, sizeof(lib_suffix), ".dylib");
#else
            snprintf(lib_suffix, sizeof(lib_suffix), ".so");
#endif
            snprintf(cmd, buf_size, "gcc -shared -fPIC ");
        } else if (m->type == MODULE_TYPE_STATICLIB) {
            snprintf(lib_suffix, sizeof(lib_suffix), ".a");
            snprintf(cmd, buf_size, "ar rcs ");
        } else {
            snprintf(cmd, buf_size, "gcc ");
        }

        // 输出文件
        if (is_shared)
            snprintf(cmd + strlen(cmd), buf_size - strlen(cmd), "-o lib%s%s ", m->name, lib_suffix);
        else if (m->type == MODULE_TYPE_STATICLIB)
            snprintf(cmd + strlen(cmd), buf_size - strlen(cmd), "lib%s%s ", m->name, lib_suffix);
        else
            snprintf(cmd + strlen(cmd), buf_size - strlen(cmd), "-o %s ", m->name);

        // 源文件
        for (uint32_t j = 0; j < m->source_files->count; ++j) {
            char path[256];
            snprintf(path, sizeof(path), "./%s/%s", m->name, m->source_files->items[j]);
            snprintf(cmd + strlen(cmd), buf_size - strlen(cmd), "%s ", path);
        }

        // 收集依赖的-I路径（去重）
        char** include_paths = malloc(256 * sizeof(char*));
        size_t include_count = 0;

        // 本模块 public_inc
        for (uint32_t j = 0; j < m->public_include_paths->count; ++j) {
            char path[256];
            snprintf(path, sizeof(path), "./%s/%s", m->name, m->public_include_paths->items[j]);
            if (!str_list_contains(include_paths, include_count, path))
                include_paths[include_count++] = strdup(path);
        }

        // 依赖模块 public_inc
        for (uint32_t j = 0; j < m->dependencies->count; ++j) {
            module_t* dep = NULL;
            // 遍历order找依赖模块
            for (uint32_t k = 0; k < order->count; ++k)
                if (strcmp(order->modules[k]->name, m->dependencies->items[j]) == 0) {
                    dep = order->modules[k];
                    break;
                }
            if (!dep) continue;

            for (uint32_t k = 0; k < dep->public_include_paths->count; ++k) {
                char path[256];
                snprintf(path, sizeof(path), "./%s/%s", dep->name, dep->public_include_paths->items[k]);
                if (!str_list_contains(include_paths, include_count, path))
                    include_paths[include_count++] = strdup(path);
            }
        }

        // 添加 -I
        for (size_t j = 0; j < include_count; ++j) {
            snprintf(cmd + strlen(cmd), buf_size - strlen(cmd), "-I%s ", include_paths[j]);
            free(include_paths[j]);
        }
        free(include_paths);

        // 添加 defines
        for (uint32_t j = 0; j < m->defines->count; ++j)
            snprintf(cmd + strlen(cmd), buf_size - strlen(cmd), "-D%s ", m->defines->items[j]);

        // 默认宏
        snprintf(cmd + strlen(cmd), buf_size - strlen(cmd), "-D%s ", type == BUILD_TYPE_DEBUG ? "DEBUG" : "RELEASE");
#ifdef _WIN32
        snprintf(cmd + strlen(cmd), buf_size - strlen(cmd), "-D%s ", "WINDOWS");
#elif  __APPLE__
        snprintf(cmd + strlen(cmd), buf_size - strlen(cmd), "-D%s ", "MACOS");
#else
        snprintf(cmd + strlen(cmd), buf_size - strlen(cmd), "-D%s ", "LINUX");
#endif

        if (type == BUILD_TYPE_DEBUG) {
            snprintf(cmd + strlen(cmd), buf_size - strlen(cmd), "-g -O0 ");
        } else {
            snprintf(cmd + strlen(cmd), buf_size - strlen(cmd), "-O2 ");
        }

        // 导出宏
        if (m->export_flag) {
            char* upname = str_toupper(m->name);
            snprintf(cmd + strlen(cmd), buf_size - strlen(cmd), "-D%s_EXPORT ", upname);
            free(upname);
        }

        cmds->list[i].module_name = strdup(m->name);
        cmds->list[i].cmd = cmd;

        printf("Generated command for %s:\n  %s\n", m->name, cmd);
    }

    return cmds;
}
