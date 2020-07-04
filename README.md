# raspi4B_num_demo
基于树莓派4B与Paddle-Lite实现的手写数字识别



## 环境要求

* ARMLinux
    armLinux即可，64位与32位系统都可运行，[Paddle-Lite预编译库](https://paddle-lite.readthedocs.io/zh/latest/user_guides/release_lib.html)
    
    * gcc g++ opencv cmake的安装（以下所有命令均在设备上操作）
    ```bash
    $ sudo apt-get update
    $ sudo apt-get install gcc g++ make wget unzip libopencv-dev pkg-config
    $ wget https://www.cmake.org/files/v3.10/cmake-3.10.3.tar.gz
    $ tar -zxvf cmake-3.10.3.tar.gz
    $ cd cmake-3.10.3
    $ ./configure
    $ make
    $ sudo make install
    ```
## 安装
$ git clone https://github.com/hang245141253/raspi4B_num_demo

## 目录介绍

num文件夹下为项目源码

Paddle-Lite文件夹为Paddle-Lite的预测库，包含32位与64位的预测库。其中库版本是Paddle-LiteV2.6.0。

## 使用

进入num文件夹，提供三个脚本。cmake.sh用于编译程序，run.sh与infer_3.sh用于预测。

执行sh cmake.sh编译代码。

执行run.sh预测0-9的28x28的灰度图像；infer_3.sh预测一个RGB三通道152x148的数字3。

以下是run.sh脚本的部分代码：

```
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
```

  程序会运行10次，按键盘上的“0”即可停止运行程序（注意按“0"之前需要点击一下跳出来的图片结果预测框）
  
  项目默认环境是armlinux 64位。如果您的系统是armlinux32位的，需要自行在cmake.sh与 run.sh中将TARGET_ARCH_ABI=armv8 注释掉，并取消#TARGET_ARCH_ABI=armv7hf的注释即可。
