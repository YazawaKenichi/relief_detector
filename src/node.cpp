// SPDX-FileCopyrightText: 2024 YAZAWA Kenichi <s21c1036hn@gmail.com>
// SPDX-License-Identifier: MIT-LICENSE

#include "core.hpp"

// using namespace ReliefDetector

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<ReliefDetectors::ReliefDetector>());
    rclcpp::shutdown();
    return 0;
}

