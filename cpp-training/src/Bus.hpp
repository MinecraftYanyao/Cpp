#pragma once
#include "PoseHandler.hpp"
#include "Vehicle.hpp"

namespace adas
{

class Bus final : public IVehicle
{
public:
    void RunM(PoseHandler& pH) override
    {
        // M: Normal=1格, Fast=2格
        int steps = pH.IsFast() ? 2 : 1;
        while (steps > 0) {
            Move(pH);
            steps--;
        }
    }

    void RunL(PoseHandler& pH) override
    {
        // Bus逻辑: 无论是否加速，都是先跑完当前状态下的移动距离(RunM)，最后再转向
        RunM(pH);
        TurnLeft(pH);
    }

    void RunR(PoseHandler& pH) override
    {
        // Bus逻辑: 先跑完移动距离，再转向
        RunM(pH);
        TurnRight(pH);
    }

private:
    // 辅助函数：与 SportsCar 相同的倒车处理逻辑
    // (注：在实际工程中，这些辅助函数可以上移到 IVehicle 的基类实现中以减少重复)
    void Move(PoseHandler& pH) const
    {
        if (pH.IsReverse())
            pH.Backward();
        else
            pH.Forward();
    }

    void TurnLeft(PoseHandler& pH) const
    {
        if (pH.IsReverse())
            pH.TurnRight();
        else
            pH.TurnLeft();
    }

    void TurnRight(PoseHandler& pH) const
    {
        if (pH.IsReverse())
            pH.TurnLeft();
        else
            pH.TurnRight();
    }
};

}  // namespace adas