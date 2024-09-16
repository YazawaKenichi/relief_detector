#!/usr/bin/env python3
# coding : utf-8
# SPDX-FileCopyrightText: 2023 YAZAWA Kenichi <s21c1036hn@gmail.com>
# SPDX-License-Identifier: MIT-LICENSE
# myname_pubsub > myname_pubsub_launch.py
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    # $HOME/ros2_ws/install/myname_pubsub/share/myname_pubsub/ + config/ + myname_pubsub.param.yaml
    config = os.path.join(get_package_share_directory("relief_detector"), "config", "relief_detector.param.yaml")
    return LaunchDescription([
        Node(package = "relief_detector", executable = "relief_detection", output = "screen", parameters = [config])
        ])

