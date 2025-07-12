from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='test1',
            executable='server',
            name='server',
        ),
        Node(
            package='test1',
            executable='client1',
            name='client1',
            arguments=['1', '2', '3'],  # Example arguments, adjust as needed
        ),
    ])
