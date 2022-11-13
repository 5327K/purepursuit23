#ifndef PURE_PURSUIT_5327K_SIMULATED_DRIVE_TRAIN_H
#define PURE_PURSUIT_5327K_SIMULATED_DRIVE_TRAIN_H

#include "abstractdrivetrain.h"

struct SimulatedRobotState
{
  // center of robot
  double x, y;
  double yaw;
  double velL, velR;

  SimulatedRobotState(double x, double y, double yaw,
                      double velL = 0, double velR = 0) : x(x), y(y), yaw(yaw),
                                                          velL(velL), velR(velR){};

  void tick(int dt)
  {
    
  }
};

class SimulatedDriveTrain : public AbstractDriveTrain
{
private:
  SimulatedRobotState state;

};

#endif // PURE_PURSUIT_5327K_SIMULATED_DRIVE_TRAIN_H