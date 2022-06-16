#ifndef PURE_PURSUIT_5327K_PATH_H
#define PURE_PURSUIT_5327K_PATH_H

#include <vector>
#include <array>
#include <algorithm>

struct Waypoint
{
  // x is between -1.8 meters and 1.8 meters (according to the VEX GPS sensor)
  double x;

  // y is between -1.8 meters and 1.8 meters (according to the VEX GPS sensor)
  double y;

  double dist = -1;
  double curvature = -1;
  double targetV = -1;
};

class Path
{
public:
  using PathVector = std::vector<Waypoint>;

private:
  const double SPACING = 6;

  PathVector path;
  bool forward;

public:
  Path(PathVector path, bool forward) : path(path), forward(forward) {}

  const PathVector &getPathVector() const
  {
    return this->path;
  }
};

#endif // PURE_PURSUIT_5327K_PATH_H
