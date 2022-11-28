// #include "path/path.h"
// #include "path/pathbuilder.h"

// #include "purepursuit/purepursuit.h"
// #include "purepursuit/drivetrain.h"

// #include "okapi/api.hpp"

// #include <iostream>
// #include <sstream>

// #include <chrono>
// #include <thread>

// const double PI = 3.141592653589793238462643383279502884;

// // x = 3 inch
// // y = 6 inch
// pros::GPS gps(9, 0.0762, 0.1524);

// pros::MotorGroup leftM({-4, 5, -6});
// pros::MotorGroup rightM({1, -2, 3});

// const double gearRatio = 0.6 * PI * 3.25;

// DriveTrain driveTrain(gps, leftM, rightM, gearRatio);

// // TODO: 1800 mm -> 1.8 m because PROS documentation sucks!!1!11

// // TODO: it seems like calculating m/s will not work due to the
// // extreme complexity of converting voltage to actual velocity -
// // probably have to refactor the code to only use voltages, which
// // gives rise to the problem of only integer voltages - maybe calculate
// // everything in doubles and then convert to closest integer?

// // TODO: max velocities might not work properly (scaling in m/s and then back to -127 to 127 is scuffed)

// int main()
// {
//   using namespace std::this_thread;
//   using namespace std::chrono;

//   // run on computer
//   Path path = PathBuilder(true, 110, 20, 3)
//                   .addPoints({{-0.1, 0}, {0.5, 0.5}, {-0.5, -0.5}})
//                   .build();

//   // saved to a file (would be ofstream, then upload to microSD card )
//   std::stringstream ss;
//   ss << path;

//   std::cout << path;

//   // actual code on the robot starts here (barring the `assert` statement)
//   // on the actual robot, `ss` would be a file stream (https://pros.cs.purdue.edu/v5/tutorials/topical/filesystem.html
//   // but with ifstream/ofstream)
//   Path newPath = Path::read(ss);

//   assert(path.toString() == newPath.toString());

//   SimulatedDriveTrain driveTrain;

//   PurePursuit pursuit(driveTrain);
//   pursuit.follow()

//   std::cout << "finished \n";


//   return 0;
// }
