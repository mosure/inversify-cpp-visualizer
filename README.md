# inversify-cpp-visualizer

[![Test Ubuntu](https://github.com/mosure/inversify-cpp-visualizer/workflows/ubuntu/badge.svg)](https://github.com/Mosure/inversify-cpp-visualizer/actions?query=workflow%3Aubuntu)
[![Test MacOS](https://github.com/mosure/inversify-cpp-visualizer/workflows/macos/badge.svg)](https://github.com/Mosure/inversify-cpp-visualizer/actions?query=workflow%3Amacos)
[![Test Windows](https://github.com/mosure/inversify-cpp-visualizer/workflows/windows/badge.svg)](https://github.com/Mosure/inversify-cpp-visualizer/actions?query=workflow%3Awindows)
[![GitHub License](https://img.shields.io/github/license/mosure/inversify-cpp-visualizer)](https://raw.githubusercontent.com/mosure/inversify-cpp-visualizer/main/LICENSE)
[![GitHub Last Commit](https://img.shields.io/github/last-commit/mosure/inversify-cpp-visualizer)](https://github.com/mosure/inversify-cpp-visualizer)
[![GitHub Issues](https://img.shields.io/github/issues/mosure/inversify-cpp-visualizer)](https://github.com/mosure/inversify-cpp-visualizer/issues)
[![Average time to resolve an issue](http://isitmaintained.com/badge/resolution/mosure/inversify-cpp-visualizer.svg)](http://isitmaintained.com/project/mosure/inversify-cpp-visualizer "Average time to resolve an issue")

inversify-cpp dependency graph export tool.

![Example Dependency Graph](example/graphviz.svg "Example Dependency Graph")

## Integration

```cpp

#include <mosure/inversify.hpp>
#include <mosure/visualizer.hpp>

// for convenience
namespace inversify = mosure::inversify;
namespace inversify_visualizer = mosure::inversify_visualizer;

```

```cpp
inversify::Container<
    symbols::foo
> container;

// ...

inversify_visualizer::write_graphviz(std::cout, container);
```

## Features
*   BUILD/WORKSPACE
*   Bazel Ubuntu, macOS, Windows workflows

## Running example
`bazel run example  --enable_platform_specific_config`
