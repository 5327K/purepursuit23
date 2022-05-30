#ifndef PURE_PURSUIT_5327K_PATH_H
#define PURE_PURSUIT_5327K_PATH_H

#include <vector>

class Waypoint
{
public:
  double x, y;

  double dist = -1;
  double curvature = -1;
  double targetV = -1;

  constexpr Waypoint(double x, double y) : x(x), y(y) {}
};

class Path
{
private:
  const double SPACING = 6;

  std::vector<Waypoint> path;
  bool forward;

public:

  constexpr Path(std::vector<Waypoint> path, bool forward): path(path), forward(forward) {}
};

#endif // PURE_PURSUIT_5327K_PATH_H
