#pragma once
#include "PoseHandler.hpp"

namespace adas
{

/**
 * @brief 抽象车辆策略接口
 * 所有具体车型（如 SportsCar, Bus）都必须实现这些方法
 */
class IVehicle
{
public:
    virtual ~IVehicle() = default;

    // 纯虚函数：执行 M 指令
    virtual void RunM(PoseHandler& poseHandler) = 0;

    // 纯虚函数：执行 L 指令
    virtual void RunL(PoseHandler& poseHandler) = 0;

    // 纯虚函数：执行 R 指令
    virtual void RunR(PoseHandler& poseHandler) = 0;
};

}  // namespace adas