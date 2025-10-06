/*
 * This file is part of Rift.
 *
 * This file define the structure of module.
 */

/*
 * For example:
 * module("Render") {
 *     type SharedLib       # output .so on Linux
 *     version 1.0.0        # define the macro RENDER_VERSION version(1, 0, 0)
 *
 *     public_inc {
 *         "inc/"           # other module will add -Ipath/to/render/inc flag
 *     }
 *
 *     depends {
 *         "Math"           # add -Ipath/to/math/inc
 *         "Platform"       # add -Ipath/to/platform/inc
 *     }
 *
 *     defines {
 *         "VULKAN"         # add the 'VULKAN' macro
 *     }
 *
 *     expoort true         # if output shared library, set it true to define the 'RENDER_EXPORT'
 *
 *     # default macros:
 *     #     DEBUG or RELEASE
 *     #     LINUX, WIN32 or MACOS
 * }
 */

#ifndef BUILDER_INC_MODULE_H
#define BUILDER_INC_MODULE_H

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

typedef enum module_type_t {
    MODULE_TYPE_SHAREDLIB,
    MODULE_TYPE_STATICLIB,
    MODULE_TYPE_EXECUTABLE
} module_type_t;

typedef struct string_t {
    char*               str;
    size_t              size;
} string_t;

typedef struct string_list_t {
    string_t            items;
    size_t              count;
} string_list_t;

typedef struct module_version_t {
    uint8_t             major;
    uint8_t             minor;
    uint8_t             path;
} module_version_t;

typedef struct module_t {
    string_t            name;
    module_type_t       type;
    module_version_t    version;

    string_list_t       public_include;
    string_list_t       depends;
    string_list_t       defines;

    bool                export_flags;
} module_t;

string_t    str_of( char* s );
void        str_free( string_t* str );

string_list_t
            str_list();
void        str_list_add( string_t str );
void        str_list_free( string_list_t* slist );

module_t    module_load( string_t path );
void        module_free( module_t* module );

#endif  /* BUILDER_INC_MODULE_H */
