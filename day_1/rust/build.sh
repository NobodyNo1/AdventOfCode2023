#!/bin/bash
SCRIPT=$(readlink -f "$0")
SCRIPT_DIR_PATH=$(dirname "$SCRIPT")
PARENT_DIR="$(dirname "$SCRIPT_DIR_PATH")"
rustc ${SCRIPT_DIR_PATH}/src/main.rs -o ${SCRIPT_DIR_PATH}/build/main

if [ $? -ne 0 ]; then
    exit 1
fi

${SCRIPT_DIR_PATH}/build/main ${PARENT_DIR}