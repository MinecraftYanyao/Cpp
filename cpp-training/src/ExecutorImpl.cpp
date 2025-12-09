#include "ExecutorImpl.hpp"

#include <algorithm>

#include "Bus.hpp"        // 引入具体策略
#include "Command.hpp"    // 引入 FastCommand, ReverseCommand
#include "SportsCar.hpp"  // 引入具体策略

namespace adas
{

// 1. 实现工厂方法
std::unique_ptr<Executor> Executor::NewExecutor(const Pose& pose, VehicleType vehicleType) noexcept
{
    return std::make_unique<ExecutorImpl>(pose, vehicleType);
}

// 2. 构造函数：策略注入与指令注册
ExecutorImpl::ExecutorImpl(const Pose& pose, VehicleType vehicleType) noexcept : poseHandler(pose)
{
    // (A) 根据类型实例化具体的车辆策略
    if (vehicleType == VehicleType::SportsCar) {
        vehicle = std::make_unique<SportsCar>();
    } else if (vehicleType == VehicleType::Bus) {
        vehicle = std::make_unique<Bus>();
    }

    // (B) 注册状态类指令 (F, B)
    // 这里直接使用 Command.hpp 中定义的 Functor，绕过工厂的复杂性
    cmderMap.emplace('F', FastCommand());
    cmderMap.emplace('B', ReverseCommand());
}

Pose ExecutorImpl::Query(void) const noexcept
{
    return poseHandler.Query();
}

// 3. 核心执行逻辑
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const auto cmd : commands) {
        // 分发逻辑：
        // 如果是移动指令 (M, L, R) -> 交给 Vehicle 策略处理
        if (cmd == 'M') {
            vehicle->RunM(poseHandler);
        } else if (cmd == 'L') {
            vehicle->RunL(poseHandler);
        } else if (cmd == 'R') {
            vehicle->RunR(poseHandler);
        } else {
            // 如果是状态指令 (F, B) -> 交给 cmderMap 处理
            const auto it = cmderMap.find(cmd);
            if (it != cmderMap.end()) {
                it->second(poseHandler);
            }
        }
    }
}

}  // namespace adas