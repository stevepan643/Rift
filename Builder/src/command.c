/*
 * command.c - Rift Builder command line interface
 * 跨平台完整支持：
 *   - 静态库 / 共享库 / 可执行文件
 *   - 每个源文件独立编译
 *   - 输出统一到 output/ 文件夹
 *   - 自动创建文件夹
 *   - 保留宏、Debug/Release 选项
 */

#include "command.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#ifdef _WIN32
#include <direct.h> // _mkdir
#else
#include <sys/stat.h>
#include <sys/types.h>
#endif

static char* str_toupper(const char* s) {
    size_t len = strlen(s);
    char* out = malloc(len + 1);
    for (size_t i = 0; i < len; ++i) out[i] = (char)toupper((unsigned char)s[i]);
    out[len] = '\0';
    return out;
}

static bool str_list_contains(char** list, size_t count, const char* s) {
    for (size_t i = 0; i < count; ++i)
        if (strcmp(list[i], s) == 0) return true;
    return false;
}

// 跨平台创建多级目录
static void mkdir_p(const char* path) {
    char tmp[512];
    strncpy(tmp, path, sizeof(tmp));
    size_t len = strlen(tmp);
    if (len == 0) return;
    if (tmp[len-1] == '/' || tmp[len-1] == '\\') tmp[len-1] = 0;

    for (char* p = tmp + 1; *p; ++p) {
        if (*p == '/' || *p == '\\') {
            *p = 0;
#ifdef _WIN32
            _mkdir(tmp);
#else
            mkdir(tmp, 0755);
#endif
            *p = '/';
        }
    }
#ifdef _WIN32
    _mkdir(tmp);
#else
    mkdir(tmp, 0755);
#endif
}

commands_t* build_gen_commands(build_order_t* order, build_type_t type) {
    commands_t* cmds = calloc(1, sizeof(commands_t));
    cmds->count = 0; // 先从 0 开始，后面动态增加
    cmds->list = NULL;

    mkdir_p("output");
    mkdir_p("output/obj");

    for (uint32_t i = 0; i < order->count; ++i) {
        module_t* m = order->modules[i];
        bool is_shared = (m->type == MODULE_TYPE_SHAREDLIB);
        bool is_static = (m->type == MODULE_TYPE_STATICLIB);
        bool is_exe    = (m->type == MODULE_TYPE_EXECUTABLE);

        // 收集 include 路径
        char inc_str[1024] = "";
        for (uint32_t j = 0; j < m->public_include_paths->count; ++j) {
            char path[256];
            snprintf(path, sizeof(path), "./%s/%s", m->name, m->public_include_paths->items[j]);
            snprintf(inc_str + strlen(inc_str), sizeof(inc_str) - strlen(inc_str), "-I%s ", path);
        }

        for (uint32_t j = 0; j < m->dependencies->count; ++j) {
            module_t* dep = NULL;
            for (uint32_t k = 0; k < order->count; ++k)
                if (strcmp(order->modules[k]->name, m->dependencies->items[j]) == 0)
                    dep = order->modules[k];
            if (!dep) continue;
            for (uint32_t k = 0; k < dep->public_include_paths->count; ++k) {
                char path[256];
                snprintf(path, sizeof(path), "./%s/%s", dep->name, dep->public_include_paths->items[k]);
                snprintf(inc_str + strlen(inc_str), sizeof(inc_str) - strlen(inc_str), "-I%s ", path);
            }
        }

        // 1️⃣ 每个源文件编译成对象文件
        for (uint32_t j = 0; j < m->source_files->count; ++j) {
            char src[512], obj[512], *cmd;
            snprintf(src, sizeof(src), "./%s/%s", m->name, m->source_files->items[j]);
            char file_safe[256];
            strncpy(file_safe, m->source_files->items[j], sizeof(file_safe));
            for (char* p = file_safe; *p; ++p)
                if (*p=='/' || *p=='\\' || *p=='.') *p='_';
            snprintf(obj, sizeof(obj), "output/obj/%s_%s.o", m->name, file_safe);

            // 创建命令字符串
            cmd = calloc(1, 1024);
            snprintf(cmd, 1024, "gcc -c %s %s -o %s", src, inc_str, obj);

            // 添加宏和编译选项
            for (uint32_t k=0;k<m->defines->count;k++)
                snprintf(cmd+strlen(cmd),1024-strlen(cmd)," -D%s", m->defines->items[k]);
            snprintf(cmd+strlen(cmd),1024-strlen(cmd)," -D%s", type==BUILD_TYPE_DEBUG?"DEBUG":"RELEASE");
#ifdef _WIN32
            snprintf(cmd+strlen(cmd),1024-strlen(cmd)," -DWINDOWS");
#elif __APPLE__
            snprintf(cmd+strlen(cmd),1024-strlen(cmd)," -DMACOS");
#else
            snprintf(cmd+strlen(cmd),1024-strlen(cmd)," -DLINUX");
#endif
            if (type==BUILD_TYPE_DEBUG)
                snprintf(cmd+strlen(cmd),1024-strlen(cmd)," -g -O0");
            else
                snprintf(cmd+strlen(cmd),1024-strlen(cmd)," -O2");
            if (m->export_flag) {
                char* upname = str_toupper(m->name);
                snprintf(cmd+strlen(cmd),1024-strlen(cmd)," -D%s_EXPORT", upname);
                free(upname);
            }

            // 保存命令
            cmds->count++;
            cmds->list = realloc(cmds->list, cmds->count * sizeof(command_t));
            cmds->list[cmds->count-1].module_name = strdup(m->name);
            cmds->list[cmds->count-1].cmd = cmd;
        }

        // 2️⃣ 链接/打包命令
        char link_cmd[2048] = "";
        if (is_shared) {
            char objs[1024] = "";
            for (uint32_t j=0;j<m->source_files->count;j++){
                char file_safe[256]; strncpy(file_safe, m->source_files->items[j], sizeof(file_safe));
                for(char* p=file_safe;*p; ++p) if(*p=='/'||*p=='\\'||*p=='.') *p='_';
                char obj[512]; snprintf(obj,sizeof(obj),"output/obj/%s_%s.o",m->name,file_safe);
                snprintf(objs+strlen(objs),1024-strlen(objs),"%s ",obj);
            }
#ifdef _WIN32
            snprintf(link_cmd,sizeof(link_cmd),"gcc -shared -fPIC %s -o output/%s.dll",objs,m->name);
#else
            snprintf(link_cmd,sizeof(link_cmd),"gcc -shared -fPIC %s -o output/lib%s.so",objs,m->name);
#endif
        } else if (is_static) {
            char objs[1024] = "";
            for (uint32_t j=0;j<m->source_files->count;j++){
                char file_safe[256]; strncpy(file_safe, m->source_files->items[j], sizeof(file_safe));
                for(char* p=file_safe;*p; ++p) if(*p=='/'||*p=='\\'||*p=='.') *p='_';
                char obj[512]; snprintf(obj,sizeof(obj),"output/obj/%s_%s.o",m->name,file_safe);
                snprintf(objs+strlen(objs),1024-strlen(objs),"%s ",obj);
            }
            snprintf(link_cmd,sizeof(link_cmd),"ar rcs output/lib%s.a %s", m->name, objs);
        } else if (is_exe) {
            char objs[1024] = "";
            for (uint32_t j=0;j<m->source_files->count;j++){
                char file_safe[256]; strncpy(file_safe, m->source_files->items[j], sizeof(file_safe));
                for(char* p=file_safe;*p; ++p) if(*p=='/'||*p=='\\'||*p=='.') *p='_';
                char obj[512]; snprintf(obj,sizeof(obj),"output/obj/%s_%s.o",m->name,file_safe);
                snprintf(objs+strlen(objs),1024-strlen(objs),"%s ",obj);
            }
            snprintf(link_cmd,sizeof(link_cmd),"gcc %s -o output/%s -Loutput ", objs, m->name);
            for(uint32_t j=0;j<m->dependencies->count;j++)
                snprintf(link_cmd+strlen(link_cmd),2048-strlen(link_cmd),"-l%s ", m->dependencies->items[j]);
        }

        if(strlen(link_cmd)>0){
            cmds->count++;
            cmds->list = realloc(cmds->list, cmds->count*sizeof(command_t));
            cmds->list[cmds->count-1].module_name = strdup(m->name);
            cmds->list[cmds->count-1].cmd = strdup(link_cmd);
        }
    }

    return cmds;
}
