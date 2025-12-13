#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd -- "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
package_dir="$(cd -- "$script_dir/.." && pwd)"
repo_root="$(git -C "$package_dir" rev-parse --show-toplevel)"

cd "$repo_root"

bazelisk build //packages/emscripten-tryout/es-ext-lib:wasm_binding

bazel_dist="$repo_root/bazel-bin/packages/emscripten-tryout/es-ext-lib/wasm_binding"
mkdir -p "$package_dir/dist"
cp -f "$bazel_dist"/binding.{js,wasm,d.ts} "$package_dir/dist/"
