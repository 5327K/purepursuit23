#ifndef PURE_PURSUIT_5327K_UTIL
#define PURE_PURSUIT_5327K_UTIL

#include <cmath>

#include "../path/path.h"
#include "../path/waypoint.h"

class Util
{
public:
  /* squares a double (a^2 or a*a) */
  const static double square(const double &a)
  {
    return a * a;
  }

  /* calculates the squared distance from (0, 0) to a point (or the magnitude of 
     a vector at the origin) */
  const static double distanceSq(const double &x, const double &y)
  {
    return square(x) + square(y);
  }

  /* calculates the squared distance between two points */
  const static double distanceSq(const Waypoint &p1, const Waypoint &p2)
  {
    return distanceSq(p2.x - p1.x, p2.y - p1.y);
  }

  /* calculates the distance from (0, 0) to a point (or the magnitude of a
     vector at the origin) */
  const static double distance(const double &x, const double &y)
  {
    return std::sqrt(distanceSq(x, y));
  }

  /* calculates the distance between two points */
  const static double distance(const Waypoint &p1, const Waypoint &p2)
  {
    return std::sqrt(distanceSq(p1, p2));
  }
};

#endif // PURE_PURSUIT_5327K_UTIL
