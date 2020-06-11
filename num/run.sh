#!/bin/bash

# configure
TARGET_ARCH_ABI=armv8 # for RK3399, set to default arch abi
#TARGET_ARCH_ABI=armv7hf # for Raspberry Pi 3B
PADDLE_LITE_DIR=../Paddle-Lite

#run
cd build
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PADDLE_LITE_DIR}/libs/${TARGET_ARCH_ABI} ./num ../models/num.nb ../images/0.jpg
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PADDLE_LITE_DIR}/libs/${TARGET_ARCH_ABI} ./num ../models/num.nb ../images/1.jpg
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PADDLE_LITE_DIR}/libs/${TARGET_ARCH_ABI} ./num ../models/num.nb ../images/2.jpg
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PADDLE_LITE_DIR}/libs/${TARGET_ARCH_ABI} ./num ../models/num.nb ../images/3.jpg
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PADDLE_LITE_DIR}/libs/${TARGET_ARCH_ABI} ./num ../models/num.nb ../images/4.jpg
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PADDLE_LITE_DIR}/libs/${TARGET_ARCH_ABI} ./num ../models/num.nb ../images/5.jpg
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PADDLE_LITE_DIR}/libs/${TARGET_ARCH_ABI} ./num ../models/num.nb ../images/6.jpg
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PADDLE_LITE_DIR}/libs/${TARGET_ARCH_ABI} ./num ../models/num.nb ../images/7.jpg
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PADDLE_LITE_DIR}/libs/${TARGET_ARCH_ABI} ./num ../models/num.nb ../images/8.jpg
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:${PADDLE_LITE_DIR}/libs/${TARGET_ARCH_ABI} ./num ../models/num.nb ../images/9.jpg
