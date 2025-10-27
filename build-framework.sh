#!/bin/bash

# Define paths
SCRIPT_DIR="$(dirname "$0")"
FRAMEWORK_DIR="$SCRIPT_DIR/minNavKit"
CLIENT_DIR="$SCRIPT_DIR/minNavCLI"
BUILD_DIR="$SCRIPT_DIR/build"
FRAMEWORK_NAME="MinNavKit"

# Create build directory
mkdir -p "$BUILD_DIR"

# Build Framework
echo "Building Framework..."
echo "Compiling Static library"
swiftc -emit-library -static \
       "$FRAMEWORK_DIR/minNav.swift" \
       "$FRAMEWORK_DIR/IPCClient.swift" \
       -o "$BUILD_DIR/lib$FRAMEWORK_NAME.a"      

echo "Generating module files"
swiftc -emit-module \
       -emit-module-path "$BUILD_DIR/$FRAMEWORK_NAME.swiftmodule" \
       -module-name $FRAMEWORK_NAME \
       "$FRAMEWORK_DIR/minNav.swift" \
       "$FRAMEWORK_DIR/IPCClient.swift"
             

# Build Client
echo "Building Client"
swiftc "$CLIENT_DIR/main.swift" \
       -I "$BUILD_DIR" \
       -L "$BUILD_DIR" \
       -l$FRAMEWORK_NAME \
       -o "$BUILD_DIR/minnavcli"
