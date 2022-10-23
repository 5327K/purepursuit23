#ifndef PURE_PURSUIT_5327K_PURE_PURSUIT_H
#define PURE_PURSUIT_5327K_PURE_PURSUIT_H

#include "api.h"

#include <cassert>

#include "../path/path.h"
#include "../util/util.h"

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

    const static double circleLineIntersection(const Waypoint &start,
                                               const Waypoint &end,
                                               const Waypoint &center,
                                               const double &radius)
    {
      // adapted from https://stackoverflow.com/a/1084899/

      const Waypoint d = end - start;
      const Waypoint f = start - center;

      const double a = d.dot(d);
      const double b = 2 * f.dot(d);
      const double c = f.dot(f) - Util::square(radius);

      double discriminant = Util::square(b) - 4 * a * c;
      if (discriminant < 0)
      {
        // no intersection, return -1
        return -1;
      }

      discriminant = std::sqrt(discriminant);
      const double t1 = (-b - discriminant) / (2 * a);
      const double t2 = (-b + discriminant) / (2 * a);

      if (t1 >= 0 && t1 <= 1)
        return t1;

      if (t2 >= 0 && t2 <= 1)
        return t2;

      return -1;
    }

    const static std::optional<const Waypoint> calculateLookaheadPoint(const Path &path,
                                                                       const Waypoint &start,
                                                                       const Waypoint &end,
                                                                       const Waypoint &currPos,
                                                                       const double &lookaheadDistance,
                                                                       const bool &onLastSegment)
    {
      const double intersection = circleLineIntersection(start, end, currPos, lookaheadDistance);

      if (intersection == -1 && onLastSegment)
        return std::optional<const Waypoint>(path.path[path.path.size() - 1]);

      if (intersection == -1)
        return std::nullopt;

      const Waypoint intersectVec = end - start;
      const Waypoint segment = intersectVec * intersection;
      const Waypoint point = start + segment;

      return std::optional<const Waypoint>(point);
    }

    const static Waypoint getLookaheadPoint(const Path &path,
                                            const Waypoint &currPos,
                                            const double &lookaheadDistance,
                                            const std::size_t &currClosestPointIndex)
    {
      const std::size_t closestPointI = getClosestPointIndex(path, currPos, currClosestPointIndex);

      Waypoint result;
      bool found = false;

      for (int i = closestPointI + 1; i < path.path.size(); ++i)
      {
        const Waypoint &start = path.path[i - 1];
        const Waypoint &end = path.path[i];

        const auto lookaheadPt = calculateLookaheadPoint(path, start, end,
                                                         currPos, lookaheadDistance,
                                                         i == path.path.size() - 1);
        if (lookaheadPt.has_value())
        {
          result = *lookaheadPt;
          found = true;
          break;
        }
      }

      assert(("Did not find lookahead point! This should never happen.", found == true));

      return result;
    }

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
