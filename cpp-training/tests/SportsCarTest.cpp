#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{

// 测试跑车：普通状态下 M 指令移动 2 格
TEST(SportsCarTest, should_move_2_steps_given_M_command_in_normal_state)
{
    // given
    // 注：Executor::NewExecutor 接口稍后需修改以支持 VehicleType
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}, VehicleType::SportsCar));
    // when
    executor->Execute("M");
    // then: (0,0,N) -> (0, 2, N)
    const Pose target({0, 2, 'N'});
    ASSERT_EQ(target, executor->Query());
}

// 测试跑车：加速状态下 M 指令移动 4 格
TEST(SportsCarTest, should_move_4_steps_given_M_command_in_fast_state)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}, VehicleType::SportsCar));
    executor->Execute("F");  // 加速
    // when
    executor->Execute("M");
    // then: (0,0,N) -> (0, 4, N)
    const Pose target({0, 4, 'N'});
    ASSERT_EQ(target, executor->Query());
}

// 测试跑车：左转逻辑（先转后走）
TEST(SportsCarTest, should_turn_left_then_move_given_L_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}, VehicleType::SportsCar));
    // when
    executor->Execute("L");
    // then:
    // 1. TurnLeft -> Facing W
    // 2. Move 1 step -> (-1, 0)
    const Pose target({-1, 0, 'W'});
    ASSERT_EQ(target, executor->Query());
}

// 测试跑车：右转逻辑（先转后走）
TEST(SportsCarTest, should_turn_right_then_move_given_R_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}, VehicleType::SportsCar));
    // when
    executor->Execute("R");
    // then:
    // 1. TurnRight -> Facing E
    // 2. Move 1 step -> (1, 0)
    const Pose target({1, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}

}  // namespace adas