#ifndef PURE_PURSUIT_5327K_DRIVE_TRAIN_H
#define PURE_PURSUIT_5327K_DRIVE_TRAIN_H

#include "main.h"

#include "abstractdrivetrain.h"

// TODO: PID? (is this handled by purepursuit already? need to check)

class DriveTrain : public AbstractDriveTrain
{
private:
  const pros::Gps &GPSsensor;
  pros::MotorGroup &leftM, &rightM;

  const double gearRatio;

public:
  /* Creates a new DriveTrain used to steer the robot with the PurePursuit
     controller.

  Arguments:
  gearRatio - the ratio of the gear train with the input at the motor and the output
  at the wheels (including the circumference of the wheels). set to 1 if there is no
  gear train and the motor directly reflects the output. */
  DriveTrain(const pros::Gps &GPSsensor, pros::MotorGroup &leftM,
             pros::MotorGroup &rightM, const double gearRatio) : GPSsensor(GPSsensor),
                                                                 leftM(leftM),
                                                                 rightM(rightM),
                                                                 gearRatio(gearRatio){};

  pros::c::gps_status_s_t getGPSSensorData()
  {
    return GPSsensor.get_status();
  }

  void setVelocities(const double &leftWheel, const double &rightWheel, const double &maxVelocity)
  {
    // TODO: do negative values (i.e. driving backwards) work?
    leftM = (leftWheel / gearRatio) / maxVelocity * 127;
    rightM = (rightWheel / gearRatio) / maxVelocity * 127;
  }
};

#endif // PURE_PURSUIT_5327K_DRIVE_TRAIN_H
