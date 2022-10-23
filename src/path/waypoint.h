#ifndef PURE_PURSUIT_5327K_WAYPOINT_H
#define PURE_PURSUIT_5327K_WAYPOINT_H

#include <vector>
#include <array>
#include <algorithm>
#include <sstream>
#include <fstream>

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

  friend std::ostream &operator<<(std::ostream &os, const Waypoint &p);

  std::string toString() const;

  static Waypoint read(std::ifstream &fin);

#pragma endregion

#pragma region Operator Overloading

  Waypoint operator+(const Waypoint &o) const;
  Waypoint &operator+=(const Waypoint &o);
  
  Waypoint operator-(const Waypoint &o) const;
  Waypoint &operator-=(const Waypoint &o);

  Waypoint operator*(const double &a) const;
  Waypoint &operator*=(const double &a);

  Waypoint operator*(const Waypoint &o) const;
  Waypoint &operator*=(const Waypoint &o);

  Waypoint operator/(const double &a) const;
  Waypoint &operator/=(const double &a);

  Waypoint operator/(const Waypoint &o) const;
  Waypoint &operator/=(const Waypoint &o);

#pragma endregion

#pragma region Other Vector Functions

  double dot(const Waypoint &o) const;

#pragma endregion
};

#endif // PURE_PURSUIT_5327K_WAYPOINT_H
