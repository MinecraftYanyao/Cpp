#pragma once
#include "PoseHandler.hpp"
#include "Vehicle.hpp"

namespace adas
{

class SportsCar final : public IVehicle
{
public:
    void RunM(PoseHandler& pH) override
    {
        // M: Normal=2格, Fast=4格
        int steps = pH.IsFast() ? 4 : 2;
        while (steps > 0) {
            Move(pH);
            steps--;
        }
    }

    void RunL(PoseHandler& pH) override
    {
        if (pH.IsFast()) {
            // F状态特殊逻辑: 进1 -> 左转 -> 进1
            Move(pH);
            TurnLeft(pH);
            Move(pH);
        } else {
            // Normal/B状态: 先左转 -> 后移动
            TurnLeft(pH);
            Move(pH);
        }
    }

    void RunR(PoseHandler& pH) override
    {
        if (pH.IsFast()) {
            // F状态特殊逻辑: 进1 -> 右转 -> 进1
            Move(pH);
            TurnRight(pH);
            Move(pH);
        } else {
            // Normal/B状态: 先右转 -> 后移动
            TurnRight(pH);
            Move(pH);
        }
    }

private:
    // 辅助函数：封装倒车逻辑 (Reverse 状态下前进变后退)
    void Move(PoseHandler& pH) const
    {
        if (pH.IsReverse())
            pH.Backward();
        else
            pH.Forward();
    }

    // 辅助函数：封装倒车转向逻辑 (Reverse 状态下左转变右转)
    void TurnLeft(PoseHandler& pH) const
    {
        if (pH.IsReverse())
            pH.TurnRight();
        else
            pH.TurnLeft();
    }

    // 辅助函数：封装倒车转向逻辑 (Reverse 状态下右转变左转)
    void TurnRight(PoseHandler& pH) const
    {
        if (pH.IsReverse())
            pH.TurnLeft();
        else
            pH.TurnRight();
    }
};

}  // namespace adas