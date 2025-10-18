#!/bin/bash
set -e

BUILD_DIR="Build"

echo "=== [RIFT BUILD] RiftCore ==="
bear -- cmake --build "$BUILD_DIR" --target RiftCore -j$(nproc)
echo "=== RiftCore build complete! ==="

