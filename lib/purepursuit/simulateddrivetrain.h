#ifndef PURE_PURSUIT_5327K_SIMULATED_DRIVE_TRAIN_H
#define PURE_PURSUIT_5327K_SIMULATED_DRIVE_TRAIN_H

#include "abstractdrivetrain.h"

#include <sstream>

struct SimulatedRobotState
{
  // track width
  const double width = 25.4;

  // center of robot
  double x, y;
  double yaw;
  double velL, velR;

  SimulatedRobotState(double x, double y, double yaw,
                      double velL = 0, double velR = 0) : x(x), y(y), yaw(yaw),
                                                          velL(velL), velR(velR){};

  void tick(double dt)
  {
    const double v = (velL + velR) / 2;
    const double w = (velL - velR) / width;

    x += v * dt * std::sin(yaw);
    y += v * dt * std::cos(yaw);
    yaw += std::atan(w * dt);
  }

  friend std::ostream &operator<<(std::ostream &os, const SimulatedRobotState &s)
  {
    os << s.x << ' ' << s.y << ' ' << s.yaw << ' ' << s.velL << ' ' << s.velR;
    return os;
  }

  std::string toString() const
  {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }
};

class SimulatedDriveTrain : public AbstractDriveTrain
{
private:
  SimulatedRobotState state{0, 0, 0};

public:
  SimulatedDriveTrain(){};
  SimulatedDriveTrain(const SimulatedRobotState &initialState) : state(initialState){};

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
    return {state.velL, state.velR};
  }

  void tick(double dt)
  {
    state.tick(dt);
  }

  const SimulatedRobotState &getState() const
  {
    return state;
  }
};

#endif // PURE_PURSUIT_5327K_SIMULATED_DRIVE_TRAIN_H