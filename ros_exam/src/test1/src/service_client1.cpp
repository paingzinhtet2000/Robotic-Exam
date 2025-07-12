#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"

#include <chrono>
#include <cstdlib>
#include <memory>

using namespace std::chrono_literals;

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);

    // Remove ROS arguments so we only get user args
    auto args = rclcpp::remove_ros_arguments(argc, argv);

    if (args.size() != 4) {  // 1 for program name + 3 args
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                    "Usage: add_three_ints_client X Y Z");
        return 1;
    }

    auto node = rclcpp::Node::make_shared("add_three_ints_client");
    auto client = node->create_client<tutorial_interfaces::srv::AddThreeInts>("add_three_ints");

    while (!client->wait_for_service(1s)) {
        if (!rclcpp::ok()) {
            RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Interrupted while waiting for the service.");
            return 1;
        }
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"), "Waiting for service to appear...");
    }

    auto request = std::make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();
    request->a = atoll(args[1].c_str());
    request->b = atoll(args[2].c_str());
    request->c = atoll(args[3].c_str());

    auto result_future = client->async_send_request(request);

    if (rclcpp::spin_until_future_complete(node, result_future) ==
        rclcpp::FutureReturnCode::SUCCESS)
    {
        RCLCPP_INFO(rclcpp::get_logger("rclcpp"),
                    "Result: %ld", result_future.get()->sum);
    } else {
        RCLCPP_ERROR(rclcpp::get_logger("rclcpp"), "Failed to call service add_three_ints");
    }

    rclcpp::shutdown();
    return 0;
}
