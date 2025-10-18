#!/bin/bash
set -e

BUILD_DIR="Build"

echo "=== [RIFT BUILD] RiftEditor ==="
bear -- cmake --build "$BUILD_DIR" --target RiftEditor -j$(nproc)
echo "=== RiftEditor build complete! ==="

