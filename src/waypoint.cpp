#include "purepursuit/purepursuit.h"

#include "util/util.h"

#include <iomanip>

#pragma region File / String Input & Output

std::ostream &operator<<(std::ostream &os, const Waypoint &p)
{
  std::streamsize ss = os.precision();
  os << std::setprecision(10) << p.x << ' ' << p.y << ' ' << p.targetV << std::setprecision(ss);
  return os;
}

std::string Waypoint::toString() const
{
  std::stringstream ss;
  ss << (*this);
  return ss.str();
}

Waypoint Waypoint::read(std::istream &fin)
{
  Waypoint result;
  result.dist = -1;
  result.curvature = -1;
  fin >> result.x >> result.y >> result.targetV;
  return result;
}

#pragma endregion

#pragma region Operator Overloading

Waypoint Waypoint::operator+(const Waypoint &o) const
{
  Waypoint newPoint = *this;
  newPoint.x += o.x;
  newPoint.y += o.y;
  return newPoint;
}

Waypoint &Waypoint::operator+=(const Waypoint &o)
{
  x += o.x;
  y += o.y;
  return *this;
}

Waypoint Waypoint::operator-(const Waypoint &o) const
{
  Waypoint newPoint = *this;
  newPoint.x -= o.x;
  newPoint.y -= o.y;
  return newPoint;
}

Waypoint &Waypoint::operator-=(const Waypoint &o)
{
  x -= o.x;
  y -= o.y;
  return *this;
}

Waypoint Waypoint::operator*(const double &a) const
{
  Waypoint newPoint = *this;
  newPoint.x *= a;
  newPoint.y *= a;
  return newPoint;
}

Waypoint &Waypoint::operator*=(const double &a)
{
  x *= a;
  y *= a;
  return *this;
}

Waypoint Waypoint::operator*(const Waypoint &o) const
{
  Waypoint newPoint = *this;
  newPoint.x *= o.x;
  newPoint.y *= o.y;
  return newPoint;
}

Waypoint &Waypoint::operator*=(const Waypoint &o)
{
  x *= o.x;
  y *= o.y;
  return *this;
}

Waypoint Waypoint::operator/(const double &a) const
{
  Waypoint newPoint = *this;
  newPoint.x /= a;
  newPoint.y /= a;
  return newPoint;
}

Waypoint &Waypoint::operator/=(const double &a)
{
  x /= a;
  y /= a;
  return *this;
}

Waypoint Waypoint::operator/(const Waypoint &o) const
{
  Waypoint newPoint = *this;
  newPoint.x /= o.x;
  newPoint.y /= o.y;
  return newPoint;
}

Waypoint &Waypoint::operator/=(const Waypoint &o)
{
  x /= o.x;
  y /= o.y;
  return *this;
}

#pragma endregion

#pragma region Other Vector Functions

double Waypoint::dot(const Waypoint &o) const
{
  return x * o.x + y * o.y;
}

#pragma endregion
