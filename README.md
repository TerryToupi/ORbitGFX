# ORbitGFX

ORbitGFX is the rendering layer for the ORbit engine. It is a C++20 static
library that wraps GPU resource creation, command recording, render and compute
passes, window/device lifecycle, and ImGui rendering behind a compact engine API.

The current backend is built on [Dawn](https://dawn.googlesource.com/dawn), the
native WebGPU implementation, with Shaderc, spdlog, and ImGui integrated through
CMake.

## Features

- Dawn/WebGPU renderer backend
- C++ renderer, device, window, and resource manager abstractions
- Shaders, buffers, dynamic buffers, textures, samplers, bind groups, render
  pass layouts, render passes, and frame buffers
- Draw stream encoding/decoding for compact render command submission
- Render, surface, compute, post, and UI command buffer paths
- ImGui renderer integration for editor and debugging UI
- Static CMake target exposed as `gfx::ORbit`

## Repository Layout

```text
include/                 Public renderer, resource, utility, and backend headers
src/                     Renderer implementation and Dawn backend
external/imgui/          Vendored ImGui integration
external/dawn/           Dawn submodule
external/shaderc/        Shaderc submodule
external/spdlog/         spdlog submodule
CMakeLists.txt           Library build definition
```

## Requirements

- CMake 3.16 or newer
- A C++20 compiler
- Git with submodule support
- A platform supported by Dawn/WebGPU

The Dawn, Shaderc, and spdlog dependencies are expected to be available through
the repository submodules. Dawn is configured with `DAWN_FETCH_DEPENDENCIES`
enabled, so its own dependency fetch step may run during CMake configuration.

## Getting Started

Clone the repository with submodules:

```bash
git clone --recursive git@github.com:TerryToupi/ORbitGFX.git
cd ORbitGFX
```

If the repository was already cloned without submodules, initialize them with:

```bash
git submodule update --init --recursive
```

Configure and build:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

On multi-config generators such as Visual Studio, `--config Release` selects the
configuration at build time. On single-config generators, the
`CMAKE_BUILD_TYPE` value is used during configuration.

## CMake Integration

Add ORbitGFX as a subdirectory and link against the exported alias target:

```cmake
add_subdirectory(path/to/ORbitGFX)

target_link_libraries(YourTarget
    PRIVATE
        gfx::ORbit
)
```

For executable targets that need Dawn's runtime library next to the output
binary, use the helper provided by this repository:

```cmake
copy_renderer_dlls(YourTarget)
```

## Basic Runtime Flow

Applications using ORbitGFX initialize the renderer, run work through the window
loop, and shut the renderer down when finished:

```cpp
#include <render/renderer.hpp>
#include <window.hpp>

int main()
{
    gfx::Renderer::INIT();

    gfx::Window::instance->Run([]()
    {
        // Record commands, update resources, and submit work here.
    });

    gfx::Renderer::SHUTDOWN();
    return 0;
}
```

Resource creation is centralized through `gfx::ResourceManager::instance`, while
command recording starts from `gfx::Renderer::instance->BeginCommandRecording`.

## Testing And Playground

This repository contains the renderer library itself. The testing playground,
examples, and hands-on integration space live in:

[TerryToupi/ORbitGFX_PlayGround](https://github.com/TerryToupi/ORbitGFX_PlayGround)

Use the playground when validating renderer behavior, experimenting with render
passes, or building small scenes against this library.

## License

ORbitGFX is licensed under the BSD 3-Clause License. See [LICENSE](LICENSE) for
the full license text.
