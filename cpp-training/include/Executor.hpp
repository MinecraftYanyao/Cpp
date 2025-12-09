#pragma once
#include <memory>
#include <string>
namespace adas
{
enum class VehicleType { SportsCar, Bus };
struct Pose {
    int x;
    int y;
    char heading;
};

class Executor
{
public:
    static std::unique_ptr<Executor> NewExecutor(const Pose& pose = {0, 0, 'N'},
                                                 VehicleType vehicleType = VehicleType::SportsCar) noexcept;
    Executor(void) = default;
    virtual ~Executor(void) = default;
    Executor(const Executor&) = delete;
    Executor& operator=(const Executor&) = delete;

public:
    virtual void Execute(const std::string& command) noexcept = 0;
    virtual Pose Query(void) const noexcept = 0;
};
}  // namespace adas