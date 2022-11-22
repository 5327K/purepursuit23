#ifndef PURE_PURSUIT_5327K_SIMULATED_DRIVE_TRAIN_H
#define PURE_PURSUIT_5327K_SIMULATED_DRIVE_TRAIN_H

#include "abstractdrivetrain.h"

struct SimulatedRobotState
{
  // track width
  const double width = 0.254;

  // center of robot
  double x, y;
  double yaw;
  double velL, velR;

  SimulatedRobotState(double x, double y, double yaw,
                      double velL = 0, double velR = 0) : x(x), y(y), yaw(yaw),
                                                          velL(velL), velR(velR){};

  void tick(double dt)
  {
    x += (velL + velR) / 2 * dt * std::sin(yaw);
    y += (velL + velR) / 2 * dt * std::cos(yaw);
    yaw += std::atan((velL + velR) / width * dt);
  }
};

class SimulatedDriveTrain : public AbstractDriveTrain
{
private:
  SimulatedRobotState state{0, 0, 0};

public:
  SimulatedDriveTrain(){};

  pros::c::gps_status_s_t getGPSSensorData() const
  {
    return pros::c::gps_status_s_t{
        state.x, state.y,
        -1, -1, state.yaw};
  }

  void setVelocities(const double &leftWheel, const double &rightWheel)
  {
    state.velL = leftWheel;
    state.velR = rightWheel;
  }

  std::pair<double, double> getWheelVelocities() const
  {
    std::cout << state.yaw << '\n';
    return {state.velL, state.velR};
  }

  void tick(double dt)
  {
    state.tick(dt);
  }
};

#endif // PURE_PURSUIT_5327K_SIMULATED_DRIVE_TRAIN_H