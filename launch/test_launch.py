import launch
import launch_ros.actions
import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()

    config = os.path.join(
        get_package_share_directory('cpp_parameters'),
        'config',
        'test.yaml'  # 경로를 'params.yaml'에서 'test.yaml'로 수정
    )
        
    node=Node(
        package = 'cpp_parameters',
        name = 'minimal_param_node',
        executable = 'minimal_param_node',
        namespace = 'ns1',  # 네임스페이스 유지
        parameters = [config]
    )

    ld.add_action(node)
    return ld
