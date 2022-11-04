// #ifndef PURE_PURSUIT_5327K_DRIVE_TRAIN_H
// #define PURE_PURSUIT_5327K_DRIVE_TRAIN_H

// #include "api.h"
// #include "pros/gps.h"
// #include "pros/motors.h"

// #include "abstractdrivetrain.h"

// class DriveTrain : AbstractDriveTrain
// {
// private:
//   const pros::Gps &GPSsensor;
//   const pros::Motor_Group &leftM, &rightM;

//   const double gearRatio;

// public:
//   // (motor velocity)(0.6) (2pi(3.25)) = wheel velocity
//   // calculate MOTOR velocity based on what WHEEL should be!
//   // (gear ratios!!)

//   /* Creates a new DriveTrain used to steer the robot with the PurePursuit
//      controller.

//   Arguments:
//   gearRatio - the ratio of gears with the input at the motor and the output
//   at the wheels (including the circumference of the wheels). */
//   DriveTrain(const pros::Gps &GPSsensor, const pros::MotorGroup &leftM,
//              const pros::MotorGroup &rightM, const double gearRatio) : GPSsensor(GPSsensor),
//                                                                       leftM(leftM),
//                                                                       rightM(rightM),
//                                                                       gearRatio(gearRatio){};

//   pros::gps_status_s_t getGPSSensorData()
//   {
//     return GPSsensor.get_status();
//   }

//   void setVelocities(const double &leftWheel, const double &rightWheel)
//   {
//     leftM = leftWheel / gearRatio;
//     rightM = rightWheel / gearRatio;
//   }
// }

// #endif // PURE_PURSUIT_5327K_DRIVE_TRAIN_H