#pragma once
#include "Executor.hpp"
namespace adas
{
struct Pose;  // 前置声明
class PoseHandler final
{
public:
    PoseHandler(const Pose& pose) noexcept;
    PoseHandler(const PoseHandler&) = delete;
    PoseHandler& operator=(const PoseHandler&) = delete;

    void Forward(void) noexcept;
    void Backward(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;

    // 状态接口
    void Fast(void) noexcept;
    bool IsFast(void) const noexcept;
    void Reverse(void) noexcept;
    bool IsReverse(void) const noexcept;

    Pose Query(void) const noexcept;

private:
    Pose pose;
    bool fast{false};
    bool reverse{false};
};
/*class ReverseCommand final
{
public:
    void operator()(PoseHandler& poseHandler) const noexcept

    {
        poseHandler.Reverse();
    }
};*/
}  // namespace adas
