#include "ExecutorImpl.hpp"

#include <memory>
namespace adas
{
Executor* Executor::NewExecutor(const Pose& pose) noexcept
{
    return new (std::nothrow) ExecutorImpl(pose);
}
ExecutorImpl::ExecutorImpl(const Pose& pose) noexcept : pose(pose), isFast(false)
{
}
void ExecutorImpl::Execute(const std::string& commands) noexcept
{
    for (const auto cmd : commands) {
        if (cmd == 'M') {
            if (isFast) {
                std::unique_ptr<MoveCommand> cmder = std::make_unique<MoveCommand>();
                cmder->DoOperate(*this);
            }
            std::unique_ptr<MoveCommand> cmder = std::make_unique<MoveCommand>();
            cmder->DoOperate(*this);
        } else if (cmd == 'L') {
            if (isFast) {
                std::unique_ptr<MoveCommand> cmder = std::make_unique<MoveCommand>();
                cmder->DoOperate(*this);
            }
            TurnLeft();
        } else if (cmd == 'R') {
            if (isFast) {
                std::unique_ptr<MoveCommand> cmder = std::make_unique<MoveCommand>();
                cmder->DoOperate(*this);
            }
            TurnRight();
        }
    }
}
Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas