#include <gtest/gtest.h>

#include <memory>

#include "Executor.hpp"
#include "PoseEq.hpp"

namespace adas
{

// 测试公交车：普通状态 M 移动 1 格
TEST(BusTest, should_move_1_step_given_M_command_in_normal_state)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}, VehicleType::Bus));
    // when
    executor->Execute("M");
    // then: (0, 1, N)
    const Pose target({0, 1, 'N'});
    ASSERT_EQ(target, executor->Query());
}

// 测试公交车：左转逻辑（先走后转）
TEST(BusTest, should_move_then_turn_left_given_L_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}, VehicleType::Bus));
    // when
    executor->Execute("L");
    // then:
    // 1. Move 1 step -> (0, 1, N)
    // 2. TurnLeft -> Facing W
    const Pose target({0, 1, 'W'});
    ASSERT_EQ(target, executor->Query());
}

// 测试公交车：右转逻辑（先走后转）
TEST(BusTest, should_move_then_turn_right_given_R_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}, VehicleType::Bus));
    // when
    executor->Execute("R");
    // then:
    // 1. Move 1 step -> (0, 1, N)
    // 2. TurnRight -> Facing E
    const Pose target({0, 1, 'E'});
    ASSERT_EQ(target, executor->Query());
}

// 测试公交车：加速状态下 M 移动 2 格
TEST(BusTest, should_move_2_steps_given_M_command_in_fast_state)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'N'}, VehicleType::Bus));
    executor->Execute("F");
    // when
    executor->Execute("M");
    // then: Move 1 + Move 1 = 2 steps
    const Pose target({0, 2, 'N'});
    ASSERT_EQ(target, executor->Query());
}

}  // namespace adas