#!/bin/bash

rm -rf ./_build/*
cmake -B_build/ -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=./package/ -DCMAKE_TOOLCHAIN_FILE=cmake_build_utilities/toolchain-file-linux-arm.cmake
cd ./_build/
echo "Generating package..."
make package
