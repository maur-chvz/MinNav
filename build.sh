#!/bin/bash

# Define paths
SCRIPT_DIR="$(dirname "$0")"
DAEMON_DIR="$SCRIPT_DIR/daemon"
FRAMEWORK_DIR="$SCRIPT_DIR/minNavKit"
CLI_DIR="$SCRIPT_DIR/minNavCLI"
BUILD_DIR="$SCRIPT_DIR/build"
DAEMON_OUT="$BUILD_DIR/minnavd"
CLI_OUT="$BUILD_DIR/minnavcli"
FRAMEWORK_NAME="minNavKit"

# Create build directory
mkdir -p "$BUILD_DIR"

# Compile C daemon
echo "Compiling daemon..."
gcc -o "$DAEMON_OUT" \
    "$DAEMON_DIR/main.c" \
    "$DAEMON_DIR/ipc_server.c" \
    "$DAEMON_DIR/ipc_server.h" \
    "$DAEMON_DIR/location_sim.c" \
    "$DAEMON_DIR/location_sim.h" \
    "$DAEMON_DIR/log.c" \
    "$DAEMON_DIR/log.h" \
    -pthread -lm


bash build-framework.sh 

echo "Build completed successfully."
echo "Daemon: $DAEMON_OUT"
echo "CLI: $CLI_OUT"
