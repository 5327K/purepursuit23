#ifndef PURE_PURSUIT_5327K_PATH_BUILDER_H
#define PURE_PURSUIT_5327K_PATH_BUILDER_H

#include "path.h"
#include "../util.h"

#include <vector>
#include <cmath>

class PathBuilder
{
private:
  using PathVector = std::vector<Waypoint>;

  /* Private methods to help with setting up the final path. */
  struct PathBuilderUtil
  {
  private:
    static double calcPathCurvature(const PathVector &path, const std::size_t &i)
    {
      const Waypoint &P = path[i - 1];
      const Waypoint &Q = path[i];
      const Waypoint &R = path[i + 1];

      const double PQ = Util::distance(P, Q);
      const double QR = Util::distance(Q, R);
      const double RP = Util::distance(R, P);

      const double productOfSides = PQ * QR * RP;
      const double semiPerimeter = (PQ + QR + RP) / 2;
      const double triangleArea = std::sqrt(semiPerimeter *
                                            (semiPerimeter - PQ) *
                                            (semiPerimeter - QR) *
                                            (semiPerimeter - RP));

      const double radius = productOfSides / (triangleArea * 4);
      const double curvature = 1 / radius;

      return curvature;
    }

  public:
    static PathVector injectPoints(const Waypoint &start,
                                   const Waypoint &end,
                                   const double &spacing)
    {
      // end - start
      const Waypoint sub = end - start;

      // magnitude of vector
      const double dist = Util::distance(sub.x, sub.y);

      // ceil(vector.magnitude() / spacing)
      const std::size_t numPoints = std::ceil(dist / spacing);

      // get the amount to move each step
      const Waypoint step = sub / dist * spacing;

      PathVector path;

      // add all points
      for (std::size_t i = 0; i < numPoints; ++i)
        path.push_back(start + (step * i));

      // add last point (a copy)
      path.push_back(Waypoint(end));

      return path;
    }

    static PathVector smooth(const PathVector &path,
                             const double &tolerance,
                             const double &a, const double &b)
    {
      // algorithm borrowed from FRC Team 2168, cleaned up using
      // FRC Team 3256's implementation
      PathVector newPath(path);
      double change = tolerance;

      while (change >= tolerance)
      {
        change = 0.0;
        for (std::size_t i = 1; i < path.size() - 1; ++i)
        {
          const Waypoint &oldPoint = path[i];
          const Waypoint &prevPoint = newPath[i - 1];
          const Waypoint &nextPoint = newPath[i + 1];

          Waypoint &currPoint = newPath[i];
          auto currXCopy = currPoint.x, currYCopy = currPoint.y;

          currPoint.x += a * (oldPoint.x - currPoint.x) +
                         b * (prevPoint.x + nextPoint.x - 2 * currPoint.x);

          currPoint.y += a * (oldPoint.y - currPoint.y) +
                         b * (prevPoint.y + nextPoint.y - 2 * currPoint.y);

          change += std::abs(currXCopy - currPoint.x);
          change += std::abs(currYCopy - currPoint.y);
        }
      }

      return newPath;
    }

    static void setDistances(PathVector &path)
    {
      path[0].dist = 0; // first point has a distance of 0 from the start

      for (std::size_t i = 1; i < path.size(); ++i)
      {
        // current dist = last dist + dist between the last point and this one
        path[i].dist = path[i - 1].dist + Util::distance(path[i - 1], path[i]);
      }
    }

    static PathVector setCurvatures(const PathVector &path)
    {
      PathVector newPath(path);

      newPath[0].curvature = 0;
      newPath.back().curvature = 0;

      for (std::size_t i = 1; i < path.size() - 1; ++i)
        newPath[i].curvature = calcPathCurvature(newPath, i);

      return newPath;
    }

    static void setTargetVel(PathVector &path, const double &maxVel,
                             const double &maxAccel, const double &k)
    {
      path.back().targetV = 0;

      for (std::size_t i = path.size() - 2; i >= 0; i--)
      {
        const double dist = Util::distance(path[i + 1], path[i]);
        const double maxReachableVel = std::sqrt(Util::square(path[i + 1].targetV) +
                                                 2 * maxAccel * dist);
        const double maxVelocity =
            i == 0 ? maxVel : std::min(maxVel, k / calcPathCurvature(path, i));

        path[i].targetV = std::min(maxVelocity, maxReachableVel);
      }
    }
  };

  PathVector path;
  bool forward;

  // defaults to values from PDF

  // defaults to about 6 inches (in meters)
  double spacing = 0.1524;

  double tolerance = 0.001;

  /* weight_smooth for smoothing algo (between 0.75 and 0.98)
  a larger value of b results in a smoother path */
  double b = 0.87;

  // weight_data for smoothing algo (usually set to 1 - b)
  double a = 1 - b;

  // The maximum velocity of the robot (in m/s).
  double maxVel;

  // The maximum acceleration of the robot (in m/s^2).
  double maxAccel;

  // Controls how quickly the robot should turn (generally between 1-5).
  double k;

public:
  /* Instantiates a new PathBuilder.

  Arguments:
  forward - Whether the robot should go forwards (true) or backwards (false).
  maxVel - The maximum velocity of the robot (in m/s).
  maxAccel - The maximum acceleration of the robot (in m/s^2).
  k - Controls how quickly the robot should turn (generally between 1-5). */
  PathBuilder(bool forward, double maxVel,
              double maxAccel, double k) : forward(forward),
                                           maxVel(maxVel),
                                           maxAccel(maxAccel),
                                           k(k){};

#pragma region Setters
  /* Sets the desired spacing (by default about 6 inches) of the new path
     (in meters). */
  PathBuilder &setSpacing(const double &newSpacing)
  {
    this->spacing = newSpacing;
    return *this;
  }

  /* Sets the tolerance value for the smoothing algorithm (by default 0.001). */
  PathBuilder &setTolerance(const double &newTolerance)
  {
    this->tolerance = newTolerance;
    return *this;
  }

  /* Sets weight_smooth (b) and weight_data (a) for the smoothing algorithm.
     A value between 0.75 and 0.98 is recommended for "b", and a larger value of
     "b" results in a smoother path. "a" is set to 1 - b by default. */
  PathBuilder &setAandB(const double &newB)
  {
    this->b = newB;
    this->a = 1 - newB;
    return *this;
  }

  /* Overrides the defaults and sets the value of "a" to something other than
     1 - b. */
  PathBuilder &overrideA(const double &newA)
  {
    this->a = newA;
    return *this;
  }

  /* Adds a new point to the PathBuilder (which will be smoothed and populated later)

  Arguments:
  point - The point to add to the Path. */
  PathBuilder &addPoint(Waypoint point)
  {
    this->path.push_back(point);
    return *this;
  }

  /* Adds multiple new points to the PathBuilder (which will all be smoothed and populated later)

  Arguments:
  points - The points to add to the Path. */
  PathBuilder &addPoints(PathVector points)
  {
    this->path.insert(this->path.end(), points.begin(), points.end());
    return *this;
  }
#pragma endregion

  /* Builds a path completely, including smoothing, injecting points, etc. */
  Path build() const
  {
    PathVector path;

    // Inject points between every pair of points
    for (std::size_t i = 0; i < this->path.size() - 1; ++i)
    {
      const Waypoint &currPoint = this->path[i];
      const Waypoint &nextPoint = this->path[i + 1];

      PathVector tmp = PathBuilderUtil::injectPoints(currPoint, nextPoint, this->spacing);
      path.insert(path.end(), tmp.begin(), tmp.end());
    }

    // Add the last point
    path.push_back(path.back());

    // Smooth all of the points
    if (this->tolerance != 0)
      path = PathBuilderUtil::smooth(path, tolerance, a, b);

    // Populate each point with values
    path = PathBuilderUtil::setCurvatures(path);
    PathBuilderUtil::setDistances(path);
    PathBuilderUtil::setTargetVel(path, this->maxVel, this->maxAccel, this->k);

    return Path(path, this->forward);
  }
};

#endif // PURE_PURSUIT_5327K_PATH_BUILDER_H
