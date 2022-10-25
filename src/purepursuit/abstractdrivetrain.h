#ifndef PURE_PURSUIT_5327K_ABSTRACT_DRIVE_TRAIN_H
#define PURE_PURSUIT_5327K_ABSTRACT_DRIVE_TRAIN_H

#include "api.h"

class AbstractDriveTrain
{
public:
  /* Returns the robot's GPS information. */
  virtual pros::gps_status_s_t getGPSSensorData();

  /* Sets the velocities of the drive train's left and right wheels as closely as possible. */
  virtual void setVelocities(const double &leftWheel, const double &rightWheel);
};

#endif // PURE_PURSUIT_5327K_ABSTRACT_DRIVE_TRAIN_H
