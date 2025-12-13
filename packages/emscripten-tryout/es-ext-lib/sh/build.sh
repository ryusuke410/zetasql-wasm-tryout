#!/usr/bin/env bash
set -euo pipefail

script_dir="$(cd -- "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
package_dir="$(cd -- "$script_dir/.." && pwd)"
repo_root="$(git -C "$package_dir" rev-parse --show-toplevel)"

cd "$repo_root"

bazelisk build //packages/emscripten-tryout/es-ext-lib:wasm_binding

dist_from_bazel="$repo_root/bazel-bin/packages/emscripten-tryout/es-ext-lib/dist"
mkdir -p "$package_dir/dist"
cp -f "$dist_from_bazel"/index.{js,wasm,d.ts} "$package_dir/dist/"
