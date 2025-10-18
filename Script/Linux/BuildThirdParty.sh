#!/usr/bin/env bash
set -e

BUILD_DIR="Build"

mkdir -p "$BUILD_DIR"

echo "[Rift] Building Third-Party Libraries..."

# spdlog
bear -- cmake --build "$BUILD_DIR" --target spdlog -j$(nproc)

echo "[Rift] All third-party libraries built successfully!"

