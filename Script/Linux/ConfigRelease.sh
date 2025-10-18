#!/bin/bash
set -e

BUILD_DIR="Build"
BUILD_TYPE="Release"

echo "=== [RIFT CONFIGURE] ==="
echo "Configuring project in $BUILD_DIR ($BUILD_TYPE mode)..."

# Create build directory if missing
mkdir -p "$BUILD_DIR"

# Configure project with CMake
bear -- cmake -B "$BUILD_DIR" -DCMAKE_BUILD_TYPE="$BUILD_TYPE"

echo "=== Configuration complete! ==="

