# Relief Detector

## Overview
地面に棒状の器具を当て、ロボットが走行不能となりうる凹凸・起伏・障害物を検知

検知した凹凸を回避するためのパッケージ

## Usage
## Prerequisites
- ROS2 Humble
- C++ 17

### Download and Install
1. ワークスペースにこのパッケージをクローン
    ``` cmd
    cd ~/ros2_ws/src/
    git clone https://github.com/yazawakenichi/relief_detector
    ```
2. パッケージのビルド
    ``` cmd
    cd ~/ros2_ws/
    colcon build --packages-select relief_detector
    ```
3. 実行ファイルのオーバーレイ
    ``` cmd
    source install/local_setup.bash
    ```

### Launching Node
`ros2 launch` を用いることでノードを起動することができます。

新しくターミナルを開いた場合、ノードを起動する前に `source install/local_setup.bash` することを忘れないでください。

``` cmd
ros2 launch relief_detector relief_detector_launch.py
```

## Package Description

#### Topic
|Name|Type|Description
|---|---|---
|`/`|``|

### Parameters
|Name|Type|Default|Description
|---|---|---|---
|``|``|``|
|``|``|``|

## License
このソフトウェアは、MIT License の下、再頒布および使用が許可されます。

(C) 2024 YAZAWA Kenichi

