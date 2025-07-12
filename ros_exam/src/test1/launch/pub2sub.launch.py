from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration

from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='test1',
            namespace='pub2sub',
            executable='publisher',
            name='Publisher'
        ),
        Node(
            package='test1',
            namespace='pub2sub',
            executable='subscriber',
            name='Subscriber'
        ),
    ])
