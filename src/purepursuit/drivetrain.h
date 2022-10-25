#ifndef PURE_PURSUIT_5327K_DRIVE_TRAIN_H
#define PURE_PURSUIT_5327K_DRIVE_TRAIN_H

#include "api.h"
#include "abstractdrivetrain.h"

class DriveTrain : AbstractDriveTrain
{
private:
  const pros::Gps &GPSsensor;
  const pros::MotorGroup &left, &right;

  const double gearRatio;

public:
  // (motor velocity)(0.6) (2pi(3.25)) = wheel velocity
  // calculate MOTOR velocity based on what WHEEL should be!
  // (gear ratios!!)

  /* Creates a new DriveTrain used to steer the robot with the PurePursuit
     controller.

  Arguments:
  gearRatio - the ratio of gears with the input at the motor and the output
  at the wheels (including the circumference of the wheels). */
  DriveTrain(const pros::Gps &GPSsensor, const pros::MotorGroup &left,
             const pros::MotorGroup &right, const double gearRatio) : GPSsensor(GPSsensor),
                                                                      left(left),
                                                                      right(right),
                                                                      gearRatio(gearRatio){};

  pros::gps_status_s_t getGPSSensorData()
  {
    return GPSsensor.get_status();
  }

  void setVelocities(const double &leftWheel, const double &rightWheel)
  {
    const double leftMotorVelocity = leftWheel / gearRatio;
    const double rightMotorVelocity = rightWheel / gearRatio;

    leftBack = leftMotorVelocity;
    leftFront = leftMotorVelocity;
    rightBack = rightMotorVelocity;
    rightFront = rightMotorVelocity;
  }
}

#endif // PURE_PURSUIT_5327K_DRIVE_TRAIN_H