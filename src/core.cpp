//! SPDX-FileCopyrightText: 2024 YAZAWA Kenichi <s21c1036hn@gmail.com>
//! SPDX-License-Identifier: MIT-LICENSE

#include "core.hpp"
#include "FileRW.hpp"
#include "TimeObserver.hpp"

namespace ReliefDetectors
{
//! コンストラクタ
ReliefDetector::ReliefDetector() : Node("relief_detector"), normalized_publisher_topic_("/relief_detector/bar/normalized"), adc_subscriber_topic_("/relief_detector/bar/raw"), saving_raw_data_path_("~/tmp/raw"), saving_normalized_data_path_("~/tmp/normalized"), raw_data_file_(saving_raw_data_path_), normalized_data_file_(saving_normalized_data_path_)
{
    //! 時刻取得クラスのインスタンス化
    this->tm_observer_ = TimeObserver::TimeObserver();
    std::string savingfilename = tm_observer_.now();

    std::string saving_raw_data_directory_;
    std::string saving_normalized_data_directory_;

    //! 起動時のみ読み込まれるパラメータ
    this->declare_parameter("Normalized_Publisher_Topic_Name", this->normalized_publisher_topic_);
    this->declare_parameter("ADC_Subscriber_Topic_Name", this->adc_subscriber_topic_);
    // this->declare_parameter("saving_raw_data", this->saving_raw_data_);
    // this->declare_parameter("saving_normalized_data", this->saving_normalized_data_);
    this->declare_parameter("saving_raw_data_directory", saving_raw_data_directory_);
    this->declare_parameter("saving_normalized_data_directory", saving_normalized_data_directory_);

    this->normalized_publisher_topic_ = this->get_parameter("Normalized_Publisher_Topic_Name").as_string();
    this->adc_subscriber_topic_ = this->get_parameter("ADC_Subscriber_Topic_Name").as_string();
    // this->saving_raw_data_ = this->get_parameter("saving_raw_data");
    // this->saving_normalized_data_ = this->get_parameter("saving_normalized_data");
    this->saving_raw_data_path_ = this->get_parameter("saving_raw_data_directory").as_string() + "/" + savingfilename;
    this->saving_normalized_data_path_ = this->get_parameter("saving_normalized_data_directory").as_string() + "/" + savingfilename;

    //! データをファイルに保存するインスタンスの生成
    this->raw_data_file_ = FileRW::FileRW(this->saving_raw_data_path_);
    this->normalized_data_file_ = FileRW::FileRW(this->saving_normalized_data_path_);

    //! パブリッシャインスタンス
    this->normalized_publisher_ = this->create_publisher<std_msgs::msg::Float32>(this->normalized_publisher_topic_, 10);
    //! サブスクライバインスタンス
    this->adc_subscriber_ = this->create_subscription<std_msgs::msg::Int32>(
    this->adc_subscriber_topic_, 10, std::bind(
        &ReliefDetector::adc_callback, this,
        std::placeholders::_1));
}

//! サブスクライブ コールバック
void ReliefDetector::adc_callback(const std_msgs::msg::Int32 & raw) const
{
    //! パブリッシュ値の範囲
    const int ref_max = 100;
    const int ref_min = 0;
    //! 以下の値はキャリブレーションして求めたい
    const int calib_max = 1024;
    const int calib_min = 0;

    //! 変換後の値
    std_msgs::msg::Float32 normalized;
    normalized.data = (raw.data - calib_min) * (ref_max - ref_min) / (float) (calib_max - calib_min);

    RCLCPP_INFO(this->get_logger(), "    raw    : %5d", raw.data);
    RCLCPP_INFO(this->get_logger(), "normalized : %7.3f", normalized.data);

    this->raw_data_file_.writef(std::to_string(raw.data) + "\r\n");
    this->normalized_data_file_.writef(std::to_string(normalized.data) + "\r\n");

    this->normalized_publisher_->publish(normalized);
}
}

