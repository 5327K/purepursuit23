#include "path/path.h"
#include "path/pathbuilder.h"

#include "purepursuit/purepursuit.h"
#include "purepursuit/drivetrain.h"

#include <iostream>
#include <sstream>

int main()
{
  // run on computer
  Path path = PathBuilder(true, 100, 1, 3)
                  .addPoints({{0, 0}, {100, 100}, {-100, -100}})
                  .build();

  // saved to a file
  std::stringstream ss;
  ss << path;

  // actual code on the robot starts here (barring the `assert` statement)
  Path newPath = Path::read(ss);

  assert(path.toString() == newPath.toString());

  // here, create DriveTrain, give it to PurePursuit, and then tell PurePursuit to run it with newPath.

  // (motor velocity)(0.6) (2pi(3.25)) = wheel velocity
  // calculate MOTOR velocity based on what WHEEL should be!
  // (gear ratios!!)

  // TODO: max velocities might not work properly (scaling in m/s and then back to -127 to 127 is scuffed)

  return 0;
}
