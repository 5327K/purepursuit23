#ifndef PURE_PURSUIT_5327K_PURE_PURSUIT_H
#define PURE_PURSUIT_5327K_PURE_PURSUIT_H

#include "main.h"

#include <cassert>
#include <cmath>
#include <limits>

#include "../path/path.h"
#include "../util/util.h"

#include "abstractdrivetrain.h"

class PurePursuit
{
private:
  AbstractDriveTrain &driveTrain;
  double stuckVel;

  constexpr static double lookaheadDistance = 30;
  constexpr static double robotTrack = 25.4;
  constexpr static double feedbackMultiplier = 0.01;

  // Limit on number of points to be searched during getClosestPoint.
  // Values <= 0 search all points.
  const static std::size_t closestPointSearchLimit = 0;

  std::size_t lastClosestPoint = 0;

public: // TODO: make private
  struct PurePursuitUtil
  {
  public:
    const static std::size_t getClosestPointIndex(const Path &path,
                                                  const Waypoint &currPos)
    {
      double minDist = Util::distanceSq(currPos, path.path[0]);
      std::size_t closestPoint = 0;

      for (std::size_t i = 0; i < path.path.size(); ++i)
      {
        const double currDist = Util::distanceSq(currPos, path.path[i]);
        if (currDist < minDist)
        {
          closestPoint = i;
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
      double discriminant = Util::square(b) - (4 * a * c);

      if (discriminant < 0)
      {
        // no intersection, return -1
        return -1;
      }

      discriminant = std::sqrt(discriminant);
      const double t1 = (-b - discriminant) / (2 * a);
      const double t2 = (-b + discriminant) / (2 * a);

      if (0 <= t1 && t1 <= 1)
        return t1;

      if (0 <= t2 && t2 <= 1)
        return t2;

      return -1;
    }

    const static std::pair<Waypoint, bool> getLookaheadPoint(const Path &path,
                                                             const Waypoint &currPos,
                                                             const double &lookaheadDistance,
                                                             const std::size_t &closestPointI)
    {

      for (int i = path.path.size() - 2; i >= 0; --i)
      {
        const Waypoint &start = path.path[i];
        const Waypoint &end = path.path[i + 1];

        const double intersection = circleLineIntersection(start, end, currPos, lookaheadDistance);
        if (intersection == -1)
          continue;

        return {start + (end - start) * intersection, false};
      }

      return {path.path[closestPointI], false};
    }

    const static double calculateCurvatureOfArc(const Path &path,
                                                const Waypoint &currPos,
                                                const double &heading,
                                                const Waypoint &lookahead,
                                                const double &lookaheadDistance)
    {
      const double translated = Util::PI / 2 - heading;

      const double a = -std::tan(translated);
      const double b = 1;
      const double c = (std::tan(translated) * currPos.x) - currPos.y;

      const double x = std::abs(a * lookahead.x + b * lookahead.y + c) / std::sqrt(Util::square(a) + Util::square(b));

      const double cross = (std::sin(translated) * (lookahead.x - currPos.x)) - (std::cos(translated) * (lookahead.y - currPos.y));
      const double side = cross > 0 ? 1 : (cross < 0 ? -1 : 0); // signum function = sign of cross

      const double curvature = (2 * x) / (Util::square(lookaheadDistance));
      return curvature * side;
    }

    const static double calculateLeftWheelTargetVelocity(const double &targetRobotVelocity,
                                                         const double &robotTrack,
                                                         const double &curvature,
                                                         const double &stuckVel)
    {
      const double result = targetRobotVelocity * (2 + (robotTrack * curvature)) / 2;
      return std::isnan(result) || result == 0 ? stuckVel : result;
    }

    const static double calculateRightWheelTargetVelocity(const double &targetRobotVelocity,
                                                          const double &robotTrack,
                                                          const double &curvature,
                                                          const double &stuckVel)
    {
      const double result = targetRobotVelocity * (2 - (robotTrack * curvature)) / 2;
      return std::isnan(result) || result == 0 ? stuckVel : result;
    }
  };

public:
  PurePursuit(AbstractDriveTrain &driveTrain, double stuckVel) : driveTrain(driveTrain), stuckVel(stuckVel){};

  struct TickData
  {
    bool ended;
    Waypoint lookaheadPt;
    double curvature;

    friend std::ostream &operator<<(std::ostream &os, const TickData &p)
    {
      os << p.lookaheadPt.x << ' ' << p.lookaheadPt.y << ' ' << p.lookaheadPt.curvature << ' ' << p.curvature;
      return os;
    }

    std::string toString() const
    {
      std::stringstream ss;
      ss << (*this);
      return ss.str();
    }
  };

  TickData tick(const Path &path);
  void follow(const Path &path);
};

#endif // PURE_PURSUIT_5327K_PURE_PURSUIT_H
