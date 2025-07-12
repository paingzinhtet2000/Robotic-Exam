#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

class NodeB : public rclcpp::Node
{
public:
  NodeB() : Node("node_b")
  {
    service_ = this->create_service<tutorial_interfaces::srv::AddThreeInts>(
      "add_three_ints_b", std::bind(&NodeB::handle_request, this, _1, _2));

    client_ = this->create_client<tutorial_interfaces::srv::AddThreeInts>("add_three_ints_a");

    timer_ = this->create_wall_timer(5s, std::bind(&NodeB::call_node_a, this));

    RCLCPP_INFO(this->get_logger(), "Node B ready.");
  }

private:
  void handle_request(
    const std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Request> request,
    std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Response> response)
  {
    response->sum = request->a + request->b + request->c;
    RCLCPP_INFO(this->get_logger(), "Node B handled request: %ld + %ld + %ld = %ld",
                request->a, request->b, request->c, response->sum);
  }

  void call_node_a()
  {
    if (!client_->wait_for_service(1s)) {
      RCLCPP_WARN(this->get_logger(), "Node B waiting for service add_three_ints_a...");
      return;
    }

    auto request = std::make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();
    request->a = 10;
    request->b = 20;
    request->c = 30;

    auto future = client_->async_send_request(request);
    auto result = rclcpp::spin_until_future_complete(this->get_node_base_interface(), future);
    if (result == rclcpp::FutureReturnCode::SUCCESS) {
      RCLCPP_INFO(this->get_logger(), "Node B got response from A: %ld", future.get()->sum);
    } else {
      RCLCPP_ERROR(this->get_logger(), "Node B failed to call service on A.");
    }
  }

  rclcpp::Service<tutorial_interfaces::srv::AddThreeInts>::SharedPtr service_;
  rclcpp::Client<tutorial_interfaces::srv::AddThreeInts>::SharedPtr client_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NodeB>());
  rclcpp::shutdown();
  return 0;
}
