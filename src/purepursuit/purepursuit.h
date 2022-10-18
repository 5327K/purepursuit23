#ifndef PURE_PURSUIT_5327K_PURE_PURSUIT_H
#define PURE_PURSUIT_5327K_PURE_PURSUIT_H

#include "api.h"

#include "../path/path.h"
#include "../util.h"

class PurePursuit
{
private:
  const pros::Gps &GPSsensor;
  const pros::Motor &leftBack, &rightBack, &leftFront, &rightFront;

  // Limit on number of points to be searched during getClosestPoint.
  // Values <= 0 search all points.
  const static std::size_t closestPointSearchLimit = 0;

  std::size_t lastClosestPoint = 0;

  struct PurePursuitUtil
  {
  public:
    const static std::size_t getClosestPointIndex(const Path &path,
                                                  const Waypoint &currPos,
                                                  const std::size_t &currClosestPointIndex)
    {
      const std::size_t searchUntil = closestPointSearchLimit <= 0 ? path.path.size() : std::min(path.path.size(), currClosestPointIndex + closestPointSearchLimit + 1);

      double minDist = Util::distanceSq(currPos, path.path[currClosestPointIndex]);
      std::size_t closestPoint = currClosestPointIndex;

      for (std::size_t i = currClosestPointIndex + 1; i < path.path.size(); ++i)
      {
        const double currDist = Util::distanceSq(currPos, path.path[i]);
        if (currDist < minDist)
        {
          closestPoint = currClosestPointIndex;
          minDist = currDist;
        }
      }

      return closestPoint;
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
