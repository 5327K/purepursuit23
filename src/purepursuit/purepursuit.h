#ifndef PURE_PURSUIT_5327K_PURE_PURSUIT_H
#define PURE_PURSUIT_5327K_PURE_PURSUIT_H

#include "pros/gps.h"
#include "pros/motors.h"

#include "../path/path.h"

class PurePursuit
{
private:
  const pros::Gps &GPSsensor;
  const pros::Motor &leftBack, &rightBack, &leftFront, &rightFront;

  struct Util
  {
  public:
    const static Waypoint &getClosestPoint(const Path &path, const int &currClosestPoint)
    {
      for (int i = currClosestPoint; i < path.path.size(); ++i)
      {
        
      }
    };

    const static Waypoint &getLookaheadPoint(const Path &path);
    const static double calculateCurvatureOfArc(const Path &path);
  };

public:
  PurePursuit(const pros::Gps &GPSsensor, const pros::Motor &leftBack,
              const pros::Motor &rightBack, const pros::Motor &leftFront,
              const pros::Motor &rightFront) : GPSsensor(GPSsensor),
                                        leftBack(leftBack),
                                        rightBack(rightBack),
                                        leftFront(leftFront),
                                        rightFront(rightFront){};


  void follow(const Path &path) const;
};

#endif // PURE_PURSUIT_5327K_PURE_PURSUIT_H
