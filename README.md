# Rift [![License](https://img.shields.io/github/license/stevepan643/Rift.svg)](https://github.com/stevepan643/Rift/blob/main/LICENSE)

**Rift** is a lightweight 3D game engine currently available on the **Windows** platform.
It is written in modern **C++**, built for modularity and clarity, and serves as a foundation for experimenting with real-time rendering and engine architecture.

---

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/stevepan643/Rift.git
```

### 2. Initialize Submodules

```bash
git submodule update --init --recursive
```

### 3. Build

Use **CMake** with your preferred generator (e.g. Ninja, Visual Studio):

```bash
cmake -B Build -G "Ninja" -DCMAKE_BUILD_TYPE=Debug
cmake --build Build
```

---

## 🧩 Third-Party Dependencies

### [GLFW](https://github.com/glfw/glfw)

* Cross-platform OpenGL window and input library.
* License: [![License](https://img.shields.io/github/license/glfw/glfw.svg)](https://github.com/glfw/glfw/blob/master/LICENSE.md)

### [GLAD](https://github.com/Dav1dde/glad)

* OpenGL loader and extension manager.
* License: [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/Dav1dde/glad/blob/glad2/LICENSE)
  [![License: Apache 2.0](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://github.com/Dav1dde/glad/blob/glad2/LICENSE)
  [![License: Khronos Permissive](https://img.shields.io/badge/License-Khronos-lightgrey.svg)](https://github.com/Dav1dde/glad/blob/glad2/LICENSE)

### [spdlog](https://github.com/gabime/spdlog)

* Fast C++ logging library.
* License: [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/gabime/spdlog/blob/v1.x/LICENSE)

### [Dear ImGui](https://github.com/ocornut/imgui)

* Immediate-mode GUI for C++.
* License: [![License](https://img.shields.io/github/license/ocornut/imgui.svg)](https://github.com/ocornut/imgui/blob/master/LICENSE.txt)

---

## 📄 License

This project is licensed under the **MIT License** — see the [LICENSE](https://github.com/stevepan643/Rift/blob/main/LICENSE) file for details.

---

## ✨ Acknowledgments

Special thanks to the open-source community and the authors of the above libraries for their excellent work.

---

## 🧠 Inspiration

Rift is partly inspired by [TheCherno’s Hazel Engine](https://github.com/TheCherno/Hazel) series.