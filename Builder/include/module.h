/*
 * module.h
 *
 * Description:
 *  This file defines the core structures and functions for handling modules
 *  in the Rift Builder. It includes the module type, dependencies, public
 *  include paths, and functions to load module definitions.
 *
 *  module.h provides the foundation for parsing, managing, and building
 *  modules in the Rift Engine's modular build system.
 * 
 */

#ifndef RIFT_BUILDER_MODULE_H
#define RIFT_BUILDER_MODULE_H

#include "base.h"

#include <stdint.h>
#include <stdbool.h>

/* Versioning macro */
#define VER(major, minor, patch) ( ((major) << 16) | ((minor) << 8) | (patch) )

/*
 * module_type_t
 *
 * Description:
 *  Enumerates the possible types of a module in Rift Builder.
 *  
 *  - MODULE_TYPE_SHAREDLIB   : Shared library (.so on Linux, .dll on Windows)
 *  - MODULE_TYPE_STATICLIB   : Static library (.a on Linux, .lib on Windows)
 *  - MODULE_TYPE_EXECUTABLE  : Executable binary
 * 
 */
typedef enum module_type_t {
    MODULE_TYPE_SHAREDLIB,
    MODULE_TYPE_STATICLIB,
    MODULE_TYPE_EXECUTABLE
} module_type_t;

/*
 * module_t
 * 
 * Description:
 *  Represents a module in the Rift Builder system.
 * 
 *  - name                  : Name of the module
 *  - type                  : Type of the module (shared lib, static lib, executable)
 *  - version               : Version of the module
 *  - source_files          : List of source files in the module
 *  - public_include_paths  : List of public include directories
 *  - dependencies          : List of module dependencies
 *  - defines               : List of preprocessor defines
 *  - export_flag           : Whether to export this module
 */
typedef struct module_t {
    char*         name;
    module_type_t       type;
    uint32_t            version;

    string_list_t*      source_files;
    string_list_t*      public_include_paths;
    string_list_t*      dependencies;
    string_list_t*      defines;

    bool                export_flag;
} module_t;

/* Function to load a module definition from a file */
module_t* load_module_definition( const char* filepath );
/* Function to free the memory used by a module */
void free_module( module_t* module );

#endif // RIFT_BUILDER_MODULE_H
