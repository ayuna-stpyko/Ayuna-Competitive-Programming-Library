#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "${ROOT_DIR}"

chmod +x scripts/setup-hooks.sh .githooks/pre-commit

git config core.hooksPath .githooks

echo "Installed Git hooks path: $(git config core.hooksPath)"
echo "pre-commit clang-format hook is now enabled."
