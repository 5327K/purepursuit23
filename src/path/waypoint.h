#ifndef PURE_PURSUIT_5327K_WAYPOINT_H
#define PURE_PURSUIT_5327K_WAYPOINT_H

#include <vector>
#include <array>
#include <algorithm>
#include <sstream>
#include <fstream>

#include "../util.h"

struct Waypoint
{
  // Minimum value for x & y values on the GPS
  constexpr static double minCoord = -1800;

  // Maximum value for x & y values on the GPS
  constexpr static double maxCoord = 1800;

  double x;
  double y;

  double dist = -1;
  double curvature = -1;
  double targetV = -1;

#pragma region File / String Input & Output

  friend std::ostream &operator<<(std::ostream &os, const Waypoint &p)
  {
    os << p.x << p.y << p.dist << p.curvature << p.targetV;
    return os;
  }

  std::string toString() const
  {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  static Waypoint read(std::ifstream &fin)
  {
    Waypoint result;
    fin >> result.x >> result.y >> result.dist >> result.curvature >> result.targetV;
    return result;
  }

#pragma endregion

#pragma region Operator Overloading

  Waypoint operator+(const Waypoint &o) const
  {
    Waypoint newPoint = *this;
    newPoint.x += o.x;
    newPoint.y += o.y;
    return newPoint;
  }

  Waypoint &operator+=(const Waypoint &o)
  {
    x += o.x;
    y += o.y;
    return *this;
  }

  Waypoint operator-(const Waypoint &o) const
  {
    Waypoint newPoint = *this;
    newPoint.x -= o.x;
    newPoint.y -= o.y;
    return newPoint;
  }

  Waypoint &operator-=(const Waypoint &o)
  {
    x -= o.x;
    y -= o.y;
    return *this;
  }

  Waypoint operator*(const double &a) const
  {
    Waypoint newPoint = *this;
    newPoint.x *= a;
    newPoint.y *= a;
    return newPoint;
  }

  Waypoint &operator*=(const double &a)
  {
    x *= a;
    y *= a;
    return *this;
  }

  Waypoint operator*(const Waypoint &o) const
  {
    Waypoint newPoint = *this;
    newPoint.x *= o.x;
    newPoint.y *= o.y;
    return newPoint;
  }

  Waypoint &operator*=(const Waypoint &o)
  {
    x *= o.x;
    y *= o.y;
    return *this;
  }

  Waypoint operator/(const double &a) const
  {
    Waypoint newPoint = *this;
    newPoint.x /= a;
    newPoint.y /= a;
    return newPoint;
  }

  Waypoint &operator/=(const double &a)
  {
    x /= a;
    y /= a;
    return *this;
  }

  Waypoint operator/(const Waypoint &o) const
  {
    Waypoint newPoint = *this;
    newPoint.x /= o.x;
    newPoint.y /= o.y;
    return newPoint;
  }

  Waypoint &operator/=(const Waypoint &o)
  {
    x /= o.x;
    y /= o.y;
    return *this;
  }

#pragma endregion

#pragma region Other Vector Functions

  double dot(const Waypoint &o) const
  {
    return x * o.x + y * o.y;
  }

#pragma endregion
};

#endif // PURE_PURSUIT_5327K_WAYPOINT_H
