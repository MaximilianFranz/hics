# HICS — Heterogeneous Image Classification System

## Overview

**HICS** is an open source application for classifying images on heterogeneous platforms — including FPGAs and GPUs — using deep neural networks and OpenCL.

## Installation & Configuration

*See [INSTALL](INSTALL.md) and [CONFIGURE](CONFIGURE.md) for details.*

HICS has thus far been tested on Ubuntu 16.04 LTS.

## Test Coverage

First, ensure that the build directory exists and navigate to it:

```bash
mkdir coverage
cd coverage
```

On Linux, you can then obtain test coverage as follows:

```bash
cmake -DCMAKE_BUILD_TYPE=Coverage ..
make -j4
make test_coverage
```

## Bug Tracking

We use [GitHub issues](https://github.com/hics-project/hics/issues) for reporting bugs and suggestions.

## License

Code is licensed under the terms of the [MIT License](LICENSE).
