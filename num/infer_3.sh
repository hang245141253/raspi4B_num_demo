#!/bin/bash

# configure
TARGET_ARCH_ABI=armv8 # for RK3399, set to default arch abi
#TARGET_ARCH_ABI=armv7hf # for Raspberry Pi 3B
PADDLE_LITE_DIR=../Paddle-Lite

#run
cd build
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PADDLE_LITE_DIR}/libs/${TARGET_ARCH_ABI} ./num ../models/num.nb ../images/infer_3.png
