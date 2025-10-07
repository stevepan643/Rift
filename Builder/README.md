# Rift Builder

**Rift Builder** is the modular build system of the **Rift Engine**, 
fully written in **C**.

It automatically parses module definition files, resolves dependencies, 
and generates build commands — without relying on CMake, Makefiles, 
or any external tools.


## 🧩 Design Goals

- Pure C implementation — no external build tools required  
- Simple modular structure  
- Automatic dependency resolution and build order generation  
- Clean and explicit command generation  
- Easy to extend and embed into the Rift engine  


## ⚙️ How It Works

1. The Builder reads all module definition files named `module.build`.  
2. Each file is parsed using `module_load()`, extracting:
    - **Module Name**
    - **Type** (`Executable`, `Shared`, or `Static`)
    - **Dependencies**
    - **Public Include Paths**
3. A dependency graph is built and sorted.
4. `build_gen_commands()` generates compile and link commands.
5. `build_build()` executes the actual build process.

> The dependency graph is implemented as a Directed Acyclic Graph (DAG),  
> ensuring modules are always built in the correct order.


## 📜 Module Definition Syntax

Example of a module definition file:

```txt
# This is the Render module

module("Render") {
    type SharedLib        # Output .so on Linux
    version 1.0.0         # Define the macro RENDER_VERSION version(1, 0, 0)

    sources {
        "src/*.c"
    }

    public_inc {
        "inc/"            # Other modules will add -Ipath/to/render/inc
    }

    dependencies {
        "Math"            # Add -Ipath/to/math/inc
        "Platform"        # Add -Ipath/to/platform/inc
    }

    defines {
        "VULKAN"          # Add the 'VULKAN' macro
    }

    export true           # If output is a shared library, set this to true to define 'RENDER_EXPORT'

    # Default macros:
    #     DEBUG or RELEASE
    #     LINUX, WIN32, or MACOS
}
```

## 🧰 Public API

```c
/* Load a module definition */
module_t module_load( string_t path );

/* Load dependency modules and generate a graph */
graph_t graph_gen_graph( module_t module );

/* Order the graph */
build_order_t build_order( graph_t graph );

/* Generate build commands based on build order */
commands_t build_gen_commands( build_order_t order );

/* Execute the build */
bool build_build( commands_t cmd );
```

## 🚀 Usage
```bash
# Build all modules
$ ./rbuild

# Or specify a single module
$ ./rbuild Render
```

---
Created by Steve Pan