# micro-ROS Agent

## micro-ROS Agent Install and Setup
### Installing ROS 2 and the micro-ROS build system
``` bash
git clone -b $ROS_DISTRO https://github.com/micro-ROS/micro_ros_setup.git src/micro_ros_setup
```

``` bash
sudo apt update && rosdep update
rosdep install --from-paths src --ignore-src -y
```

``` bash
sudo apt-get install python3-pip
```

``` bash
colcon build --packages-select micro_ros_setup --cmake-args -DUAGENT_USE_SYSTEM_LOGGER=ON
source install/local_setup.bash
```

### Creating a new firmware workspace
``` bash
ros2 run micro_ros_setup create_firmware_ws.sh host
```

### Building the firmware
``` bash
ros2 run micro_ros_setup build_firmware.sh
source install/local_setup.bash
```

### Creating the micro-ROS agent
``` bash
ros2 run micro_ros_setup create_agent_ws.sh
```

``` bash
ros2 run micro_ros_setup build_agent.sh
source install/local_setup.sh
```

## Running the micro-ROS app
``` bash
ros2 run micro_ros_agent micro_ros_agent serial -b 11500 --dev /dev/ttyACM0 -v6
```





