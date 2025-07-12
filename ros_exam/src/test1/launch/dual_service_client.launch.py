from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='test1',
            executable='dual_node_a',
            name='node_a'
        ),
        Node(
            package='test1',
            executable='dual_node_b',
            name='node_b'
        )
    ])
