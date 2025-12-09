#pragma once
#include <functional>

#include "PoseHandler.hpp"

namespace adas
{

/**
 * @brief 状态控制命令
 * 注意：移动指令(M, L, R)已移交 IVehicle 策略处理，此处仅保留状态切换指令
 */

class FastCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Fast();
    }
};

class ReverseCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept
    {
        poseHandler.Reverse();
    }
};

}  // namespace adas