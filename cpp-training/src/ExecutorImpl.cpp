#include "ExecutorImpl.hpp"

#include <memory>
#include <unordered_map>

#include "Command.hpp"

namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : poseHandler(pose)
{
}
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    std::unordered_map<char, std::unique_ptr<ICommand>> cmderMap;
    cmderMap.emplace('M', std::make_unique<MoveCommand>());
    cmderMap.emplace('L', std::make_unique<TurnLeftCommand>());
    cmderMap.emplace('R', std::make_unique<TurnRightCommand>());
    cmderMap.emplace('F', std::make_unique<FastCommand>());
    for (const auto cmd : commands) {
        const auto it = cmderMap.find(cmd);

        if (it != cmderMap.end()) {
            it->second->DoOperate(poseHandler);
        }
    }
}
Pose ExecutorImpl::Query() const noexcept
{
    return poseHandler.Query();
}
void ExecutorImpl::Move(void) noexcept
{
    if (pose.heading == 'E') {
        ++pose.x;
    } else if (pose.heading == 'W') {
        --pose.x;
    } else if (pose.heading == 'N') {
        ++pose.y;
    } else if (pose.heading == 'S') {
        --pose.y;
    }
}
void ExecutorImpl::TurnLeft(void) noexcept
{
    if (pose.heading == 'E') {
        pose.heading = 'N';
    } else if (pose.heading == 'N') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'E';
    }
}
void ExecutorImpl::TurnRight(void) noexcept
{
    if (pose.heading == 'E') {
        pose.heading = 'S';
    } else if (pose.heading == 'S') {
        pose.heading = 'W';
    } else if (pose.heading == 'W') {
        pose.heading = 'N';
    } else if (pose.heading == 'N') {
        pose.heading = 'E';
    }
}
void ExecutorImpl::Fast() noexcept
{
    fast = !fast;
}
bool ExecutorImpl::IsFast() const noexcept
{
    return fast;
}

}  // namespace adas