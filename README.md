## Task 01
### What this repository for
* 熟悉物体检测
* 熟悉摄像机内参
* 熟悉不同坐标系之间的转换

### Usage

```bash
$ git clone https://github.com/b51/robot_tutorial_01
$ cd robot_tutorial_01
$ mkdir build
$ cd build
$ cmake ..
$ make -j
$ ./detect_ball ../data/ball_image.jpg
```

### Task
* 补充 ImageProcess.cc 内的 DetectBall 完成对图片中球的检测
* 使用提供的 K 计算出球心在相机坐标系中的坐标
* 使用提供的相机与机器人之间的外参计算出球心在机器人坐标系中的坐标
