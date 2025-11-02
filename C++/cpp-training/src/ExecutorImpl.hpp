#pragma once
#include "Executor.hpp"
namespace adas
{
class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose) noexcept;
    ~ExecutorImpl() noexcept = default;
    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

public:
    void Execute(const std::string& command) noexcept override;
    Pose Query(void) const noexcept override;

private:
    Pose pose;
    bool isFast = false;
    void Move(void) noexcept
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
    void TurnLeft(void) noexcept
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
    void TurnRight(void) noexcept
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

private:
    class MoveCommand final
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept
        {
            executor.Move();
        }
    };
};
}  // namespace adas