#include "rclcpp/rclcpp.hpp"
#include "tutorial_interfaces/srv/add_three_ints.hpp"

using namespace std::chrono_literals;
using std::placeholders::_1;
using std::placeholders::_2;

class NodeA : public rclcpp::Node
{
public:
  NodeA() : Node("node_a")
  {
    // Create the service
    service_ = this->create_service<tutorial_interfaces::srv::AddThreeInts>(
      "add_three_ints_a", std::bind(&NodeA::handle_request, this, _1, _2));

    // Create the client to call Node B's service
    client_ = this->create_client<tutorial_interfaces::srv::AddThreeInts>("add_three_ints_b");

    // Periodic call to Node B
    timer_ = this->create_wall_timer(3s, std::bind(&NodeA::call_node_b, this));

    RCLCPP_INFO(this->get_logger(), "Node A ready.");
  }

private:
  void handle_request(
    const std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Request> request,
    std::shared_ptr<tutorial_interfaces::srv::AddThreeInts::Response> response)
  {
    response->sum = request->a + request->b + request->c;
    RCLCPP_INFO(this->get_logger(), "Node A handled request: %ld + %ld + %ld = %ld",
                request->a, request->b, request->c, response->sum);
  }

  void call_node_b()
  {
    if (!client_->wait_for_service(1s)) {
      RCLCPP_WARN(this->get_logger(), "Node A waiting for service add_three_ints_b...");
      return;
    }

    auto request = std::make_shared<tutorial_interfaces::srv::AddThreeInts::Request>();
    request->a = 1;
    request->b = 2;
    request->c = 3;

    auto future = client_->async_send_request(request);
    auto result = rclcpp::spin_until_future_complete(this->get_node_base_interface(), future);
    if (result == rclcpp::FutureReturnCode::SUCCESS) {
      RCLCPP_INFO(this->get_logger(), "Node A got response from B: %ld", future.get()->sum);
    } else {
      RCLCPP_ERROR(this->get_logger(), "Node A failed to call service on B.");
    }
  }

  rclcpp::Service<tutorial_interfaces::srv::AddThreeInts>::SharedPtr service_;
  rclcpp::Client<tutorial_interfaces::srv::AddThreeInts>::SharedPtr client_;
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<NodeA>());  // or NodeB
  rclcpp::shutdown();
  return 0;
}
