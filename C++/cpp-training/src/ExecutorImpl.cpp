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
        std::unique_ptr<ICommand> cmder;

        if (cmd == 'M') {
            if (isFast) {
                cmder = std::make_unique<MoveCommand>();
            }
            cmder = std::make_unique<MoveCommand>();
        } else if (cmd == 'L') {
            if (isFast) {
                cmder = std::make_unique<MoveCommand>();
            }
            cmder = std::make_unique<TurnLeftCommand>();
        } else if (cmd == 'R') {
            if (isFast) {
                cmder = std::make_unique<MoveCommand>();
            }
            cmder = std::make_unique<TurnRightCommand>();
        }

        if (cmder) {
            cmder->DoOperate(*this);
        }
    }
}
Pose ExecutorImpl::Query() const noexcept
{
    return pose;
}
}  // namespace adas