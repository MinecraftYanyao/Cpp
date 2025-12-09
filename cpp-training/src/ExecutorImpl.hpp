#pragma once
#include <functional>
#include <memory>  // 引入智能指针
#include <unordered_map>

#include "Executor.hpp"
#include "PoseHandler.hpp"
#include "Vehicle.hpp"  // 引入策略接口

namespace adas
{
class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose, VehicleType vehicleType) noexcept;
    ~ExecutorImpl() noexcept = default;
    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

public:
    void Execute(const std::string& command) noexcept override;
    Pose Query(void) const noexcept override;

    /*public:
        bool IsFast(void) const noexcept;
        void Fast(void) noexcept;
        void Move(void) noexcept;
        void TurnLeft(void) noexcept;
        void TurnRight(void) noexcept;

    private:
        Pose pose;
        bool fast{false};*/

private:
    PoseHandler poseHandler;
    // 策略对象
    std::unique_ptr<IVehicle> vehicle;

    // 命令映射表 (处理 F, B)
    std::unordered_map<char, std::function<void(PoseHandler&)>> cmderMap;
};
}  // namespace adas