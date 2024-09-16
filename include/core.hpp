// SPDX-FileCopyrightText: 2024 YAZAWA Kenichi <s21c1036hn@gmail.com>
// SPDX-License-Identifier: MIT-LICENSE

#ifndef CORE_HPP_
#define CORE_HPP_

#include <iostream>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int32.hpp"
#include "std_msgs/msg/float32.hpp"

#include "FileRW.hpp"
#include "TimeObserver.hpp"

namespace ReliefDetectors
{
class ReliefDetector : public rclcpp::Node
{
public:
  ReliefDetector();

private:
  void timer_cb();
  void adc_callback(const std_msgs::msg::Int32 &) const;

  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr normalized_publisher_;
  rclcpp::Subscription<std_msgs::msg::Int32>::SharedPtr adc_subscriber_;
  std::string normalized_publisher_topic_;
  std::string adc_subscriber_topic_;
  //! データの値をファイルに保存する
  // bool saving_raw_data_;
  std::string saving_raw_data_path_;
  // bool saving_normalized_data_;
  std::string saving_normalized_data_path_;

  FileRW::FileRW raw_data_file_;
  FileRW::FileRW normalized_data_file_;
  TimeObserver::TimeObserver tm_observer_;
};
}

#endif

