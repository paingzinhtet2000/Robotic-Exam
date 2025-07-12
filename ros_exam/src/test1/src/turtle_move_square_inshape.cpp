#include <functional>
#include <memory>
#include <sstream>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "turtlesim/msg/pose.hpp"

using namespace std::chrono_literals;

class FramePublisher : public rclcpp::Node
{
public:
  FramePublisher()
  : Node("turtle_square_tf_publisher"), state_(0), tick_count_(0), side_count_(0)
  {
    // Declare and get turtlename parameter
    turtlename_ = this->declare_parameter<std::string>("turtlename", "turtle1");

    // TF broadcaster
    tf_broadcaster_ = std::make_unique<tf2_ros::TransformBroadcaster>(*this);

    // Subscribe to pose topic
    std::string topic_name = "/" + turtlename_ + "/pose";
    subscription_ = this->create_subscription<turtlesim::msg::Pose>(
      topic_name, 10, std::bind(&FramePublisher::handle_turtle_pose, this, std::placeholders::_1));

    // Publisher for movement
    publisher_ = this->create_publisher<geometry_msgs::msg::Twist>("/" + turtlename_ + "/cmd_vel", 10);

    // Timer to control motion
    timer_ = this->create_wall_timer(500ms, std::bind(&FramePublisher::move_square, this));

    RCLCPP_INFO(this->get_logger(), "Square movement with TF publishing started.");
  }

private:
  // Publishes TF transform from pose
  void handle_turtle_pose(const std::shared_ptr<turtlesim::msg::Pose> msg)
  {
    geometry_msgs::msg::TransformStamped t;
    t.header.stamp = this->get_clock()->now();
    t.header.frame_id = "world";
    t.child_frame_id = turtlename_;

    t.transform.translation.x = msg->x;
    t.transform.translation.y = msg->y;
    t.transform.translation.z = 0.0;

    tf2::Quaternion q;
    q.setRPY(0, 0, msg->theta);
    t.transform.rotation.x = q.x();
    t.transform.rotation.y = q.y();
    t.transform.rotation.z = q.z();
    t.transform.rotation.w = q.w();

    tf_broadcaster_->sendTransform(t);
  }

  // Publishes Twist commands to move in square
  void move_square()
  {
    geometry_msgs::msg::Twist cmd;

    if (state_ == 0) {  // Move forward
      cmd.linear.x = 1.0;
      cmd.angular.z = 0.0;
      tick_count_++;

      if (tick_count_ >= forward_ticks_) {
        tick_count_ = 0;
        state_ = 1;  // Switch to turning
      }
    }
    else if (state_ == 1) {  // Turn 90 degrees
      cmd.linear.x = 0.0;
      cmd.angular.z = 1.047;  // ~π/3 rad/s, so 90° in 1.5s
      tick_count_++;

      if (tick_count_ >= turn_ticks_) {
        tick_count_ = 0;
        state_ = 0;  // Switch back to moving forward
        side_count_ = (side_count_ + 1) % 4;
      }
    }

    publisher_->publish(cmd);
  }

  // Members
  std::string turtlename_;
  rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr subscription_;
  rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr publisher_;
  std::unique_ptr<tf2_ros::TransformBroadcaster> tf_broadcaster_;
  rclcpp::TimerBase::SharedPtr timer_;

  int state_;         // 0 = forward, 1 = turning
  int tick_count_;    // steps inside current state
  int side_count_;    // number of sides completed

  const int forward_ticks_ = 4;   // 0.5s x 4 = 2 seconds forward
  const int turn_ticks_ = 3;      // 0.5s x 3 = 1.5 seconds turning
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<FramePublisher>());
  rclcpp::shutdown();
  return 0;
}
