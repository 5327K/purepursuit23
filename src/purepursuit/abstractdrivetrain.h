#ifndef PURE_PURSUIT_5327K_ABSTRACT_DRIVE_TRAIN_H
#define PURE_PURSUIT_5327K_ABSTRACT_DRIVE_TRAIN_H

#include "main.h"

class AbstractDriveTrain
{
public:
  /* Returns the robot's GPS information. */
  virtual pros::c::gps_status_s_t getGPSSensorData();

  /* Sets the velocities of the drive train's left and right wheels as closely as possible, using the maxVelocity
     set in the PathBuilder in order to scale it appropriately. */
  virtual void setVelocities(const double &leftWheel, const double &rightWheel, const double &maxVelocity);
};

#endif // PURE_PURSUIT_5327K_ABSTRACT_DRIVE_TRAIN_H
