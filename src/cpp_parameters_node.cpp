#include <chrono>
#include <functional>
#include <string>

#include <rclcpp/rclcpp.hpp>

using namespace std::chrono_literals;

class MinimalParam : public rclcpp::Node
{
public:
  MinimalParam()
  : Node("minimal_param_node")
  {
    // 파라미터 설명을 추가하여 파라미터 선언
    auto param_desc = rcl_interfaces::msg::ParameterDescriptor{};
    param_desc.description = "This parameter is mine!";
    
    // 파라미터 선언 시 설명을 함께 넘겨줌
    this->declare_parameter<std::string>("my_parameter", "world", param_desc);

    // 타이머 설정
    timer_ = this->create_wall_timer(
      1000ms, std::bind(&MinimalParam::timer_callback, this));
  }

  void timer_callback()
  {
    // 파라미터 값 가져오기
    std::string my_param = this->get_parameter("my_parameter").as_string();

    // 파라미터 값을 로그로 출력
    RCLCPP_INFO(this->get_logger(), "Hello %s!", my_param.c_str());
    
  }

private:
  rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<MinimalParam>());
  rclcpp::shutdown();
  return 0;
}