#ifndef PURE_PURSUIT_5327K_PURE_PURSUIT_H
#define PURE_PURSUIT_5327K_PURE_PURSUIT_H

#include "main.h"

#include <cassert>
#include <cmath>

#include "../path/path.h"
#include "../util/util.h"

#include "abstractdrivetrain.h"

class PurePursuit
{
private:
  AbstractDriveTrain &driveTrain;

  constexpr static double lookaheadDistance = 0.05;
  constexpr static double robotTrack = 0.254;
  constexpr static double feedbackMultiplier = 0.01;

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
      std::cout << searchUntil << '\n';

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

    const static std::pair<std::optional<const Waypoint>, bool> calculateLookaheadPoint(const Path &path,
                                                                       const Waypoint &start,
                                                                       const Waypoint &end,
                                                                       const Waypoint &currPos,
                                                                       const double &lookaheadDistance,
                                                                       const bool &onLastSegment)
    {
      const double intersection = circleLineIntersection(start, end, currPos, lookaheadDistance);

      if (intersection == -1 && onLastSegment)
        return {std::optional<const Waypoint>(path.path[path.path.size() - 1]), true};

      if (intersection == -1)
        return {std::nullopt, false};

      const Waypoint intersectVec = end - start;
      const Waypoint segment = intersectVec * intersection;
      const Waypoint point = start + segment;

      return {std::optional<const Waypoint>(point), false};
    }

    const static std::pair<Waypoint, bool> getLookaheadPoint(const Path &path,
                                            const Waypoint &currPos,
                                            const double &lookaheadDistance,
                                            const std::size_t &closestPointI)
    {
      // TODO: return index so an end condition can be set properly
      Waypoint result;
      bool found = false;
      bool isLast = false;

      for (int i = closestPointI + 1; i < path.path.size(); ++i)
      {
        const Waypoint &start = path.path[i - 1];
        const Waypoint &end = path.path[i];

        const auto [lookaheadPt, isEnd] = calculateLookaheadPoint(path, start, end,
                                                         currPos, lookaheadDistance,
                                                         i == path.path.size() - 1);
        if (lookaheadPt.has_value())
        {
          result = *lookaheadPt;
          found = true;
          isLast = isEnd;
          break;
        }
      }

      assert(("Did not find lookahead point! This should never happen.", found == true));

      return {result, isLast};
    }

    const static double calculateCurvatureOfArc(const Path &path,
                                                const Waypoint &currPos,
                                                const double &heading,
                                                const Waypoint &lookahead,
                                                const double &lookaheadDistance)
    {
      const double a = -std::tan(heading);
      const double b = 1;
      const double c = (std::tan(heading) * currPos.x) - currPos.y;

      const double x = std::abs(a * lookahead.x + b * lookahead.y + c) / std::sqrt(Util::square(a) + Util::square(b));

      const double cross = (std::sin(heading) * (lookahead.x - currPos.x)) - (std::cos(heading) * (lookahead.y - currPos.y));
      const double side = cross > 0 ? 1 : -1; // signum function = sign of cross

      const double curvature = (2 * x) / (Util::square(lookaheadDistance));
      return curvature * side;
    }

    const static double calculateLeftWheelTargetVelocity(const double &targetRobotVelocity,
                                                         const double &robotTrack,
                                                         const double &curvature)
    {
      return targetRobotVelocity * ((2 + (robotTrack * curvature))) / 2;
    }

    const static double calculateRightWheelTargetVelocity(const double &targetRobotVelocity,
                                                          const double &robotTrack,
                                                          const double &curvature)
    {
      return targetRobotVelocity * ((2 - (robotTrack * curvature))) / 2;
    }
  };

public:
  PurePursuit(AbstractDriveTrain &driveTrain) : driveTrain(driveTrain){};

  bool tick(const Path &path, int &closestPt);
  void follow(const Path &path);
};

#endif // PURE_PURSUIT_5327K_PURE_PURSUIT_H
