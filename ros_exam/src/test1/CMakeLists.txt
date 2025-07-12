cmake_minimum_required(VERSION 3.8)
project(test1)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(tutorial_interfaces REQUIRED)
find_package(tf2 REQUIRED)
find_package(tf2_ros REQUIRED)
find_package(turtlesim REQUIRED)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # comment the line when a copyright and license is added to all source files
  set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # comment the line when this package is in a git repo and when
  # a copyright and license is added to all source files
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

add_executable(publisher src/publisher.cpp)
ament_target_dependencies(publisher rclcpp std_msgs)

add_executable(subscriber src/subscriber.cpp)
ament_target_dependencies(subscriber rclcpp std_msgs)

add_executable(publisher2 src/pub_custom.cpp)
ament_target_dependencies(publisher2 rclcpp tutorial_interfaces)

add_executable(subscriber2 src/sub_custom.cpp)
ament_target_dependencies(subscriber2 rclcpp tutorial_interfaces)

add_executable(client src/service_client.cpp)
ament_target_dependencies(client rclcpp tutorial_interfaces)

add_executable(client1 src/service_client1.cpp)
ament_target_dependencies(client1 rclcpp tutorial_interfaces)

add_executable(server src/service_server.cpp)
ament_target_dependencies(server rclcpp tutorial_interfaces)

add_executable(moving_turtle src/turtle_move_square_inshape.cpp)
ament_target_dependencies(
  moving_turtle
  geometry_msgs
  rclcpp
  tf2
  tf2_ros
  turtlesim
)

install(TARGETS
  publisher
  publisher2
  subscriber
  subscriber2
  client
  server
  client1
  moving_turtle
  DESTINATION lib/${PROJECT_NAME}
)

add_executable(dual_node_a src/dual_service_client_a.cpp)
ament_target_dependencies(dual_node_a rclcpp tutorial_interfaces)

add_executable(dual_node_b src/dual_service_client_b.cpp)
ament_target_dependencies(dual_node_b rclcpp tutorial_interfaces)

install(TARGETS
  dual_node_a
  dual_node_b
  DESTINATION lib/${PROJECT_NAME}
)

add_executable(static_br src/static_tf2_br.cpp)
ament_target_dependencies(
  static_br
  geometry_msgs
  rclcpp
  tf2
  tf2_ros
)

add_executable(turtle_tf2_broadcaster src/tf2_publisher.cpp)
ament_target_dependencies(
    turtle_tf2_broadcaster
    geometry_msgs
    rclcpp
    tf2
    tf2_ros
    turtlesim
)

add_executable(listener src/tf2_listener.cpp)
ament_target_dependencies(
    listener
    geometry_msgs
    rclcpp
    tf2
    tf2_ros
    turtlesim
)

add_executable(fixed_frame_tf2_br src/fixed_frame_tf2_br.cpp)
ament_target_dependencies(
    fixed_frame_tf2_br
    geometry_msgs
    rclcpp
    tf2
    tf2_ros
    turtlesim
)

install(TARGETS
  static_br
  turtle_tf2_broadcaster
  listener
  fixed_frame_tf2_br
  DESTINATION lib/${PROJECT_NAME}
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
