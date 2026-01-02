#!/bin/sh

set -e  # Exit on error

# === Configuration ===
CXX=g++
OUT_DIR=./build
TARGET=$OUT_DIR/p

SRC_DIR=./src
LIB_DIR=./lib
INCLUDE_DIR=$LIB_DIR/include

# Source files
SRC_FILES="$SRC_DIR/*.cpp $LIB_DIR/glad.c"

# Compiler flags
CXXFLAGS="-Wall -std=c++17 -I$INCLUDE_DIR -g"
LDFLAGS="-ldl -lglfw"

# === Build ===
mkdir -p "$OUT_DIR"
echo "Compiling..."
$CXX $CXXFLAGS -o "$TARGET" $SRC_FILES $LDFLAGS

echo "Build complete: $TARGET"
"$TARGET"
