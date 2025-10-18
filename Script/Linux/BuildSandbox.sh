#!/bin/bash
set -e

BUILD_DIR="Build"

echo "=== [RIFT BUILD] Sandbox ==="
bear -- cmake --build "$BUILD_DIR" --target Sandbox -j$(nproc)
echo "=== Sandbox build complete! ==="

