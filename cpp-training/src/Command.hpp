#pragma once
#include <functional>

#include "ExecutorImpl.hpp"
#include "PoseHandler.hpp"

namespace adas
{
// class ICommand
//{
// public:
//     virtual ~ICommand() = default;
//     virtual void DoOperate(PoseHandler& poseHandler) const noexcept = 0;
// };
class MoveCommand final  //: public ICommand
{
public:
    // void DoOperate(PoseHandler& poseHandler) const noexcept override
    //{
    //     if (poseHandler.IsFast()) {
    //         poseHandler.Move();
    //     }

    //    poseHandler.Move();
    //}
    void operator()(PoseHandler& poseHandler) const noexcept

    {
        if (poseHandler.IsFast()) {
            if (poseHandler.IsReverse()) {
                poseHandler.Backward();

            } else {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse()) {
            poseHandler.Backward();

        } else {
            poseHandler.Forward();
        }
    }
};
class TurnLeftCommand final  //: public ICommand
{
public:
    // void DoOperate(PoseHandler& poseHandler) const noexcept override
    //{
    //     if (poseHandler.IsFast()) {
    //         poseHandler.Move();
    //     }
    //     poseHandler.TurnLeft();
    // }
    void operator()(PoseHandler& poseHandler) const noexcept

    {
        if (poseHandler.IsFast()) {
            if (poseHandler.IsReverse()) {
                poseHandler.Backward();

            } else {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse()) {
            poseHandler.TurnRight();

        } else {
            poseHandler.TurnLeft();
        }
    }
};
class TurnRightCommand final  //: public ICommand
{
public:
    // void DoOperate(PoseHandler& poseHandler) const noexcept override
    //{
    //     if (poseHandler.IsFast()) {
    //         poseHandler.Move();
    //     }
    //     poseHandler.TurnRight();
    // }
    void operator()(PoseHandler& poseHandler) const noexcept

    {
        if (poseHandler.IsFast()) {
            if (poseHandler.IsReverse()) {
                poseHandler.Backward();

            } else {
                poseHandler.Forward();
            }
        }
        if (poseHandler.IsReverse()) {
            poseHandler.TurnLeft();

        } else {
            poseHandler.TurnRight();
        }
    }
};
class FastCommand final  //: public ICommand
{
public:
    // void DoOperate(PoseHandler& poseHandler) const noexcept override

    //{
    //    poseHandler.Fast();
    //}
    void operator()(PoseHandler& poseHandler) const noexcept

    {
        poseHandler.Fast();
    }
};
}  // namespace adas