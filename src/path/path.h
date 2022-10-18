#ifndef PURE_PURSUIT_5327K_PATH_H
#define PURE_PURSUIT_5327K_PATH_H

#include <vector>
#include <array>
#include <algorithm>
#include <sstream>
#include <fstream>

struct Waypoint
{
  // Minimum value for x & y values on the GPS
  const static double minCoord = -1800;

  // Maximum value for x & y values on the GPS
  const static double maxCoord = 1800;

  double x;
  double y;

  double dist = -1;
  double curvature = -1;
  double targetV = -1;

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
};

class Path
{
public:
  using PathVector = std::vector<Waypoint>;

private:
  const double SPACING = 6;

public:
  const PathVector path;
  const bool forward;

  Path(const PathVector path, const bool forward) : path(path), forward(forward) {}

  friend std::ostream &operator<<(std::ostream &os, const Path &p)
  {
    os << p.forward << ' ' << p.path.size() << '\n';
    for (const auto &point : p.path)
      os << point;

    return os;
  }

  std::string toString() const
  {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  static Path read(std::ifstream &fin)
  {
    bool forward;
    std::size_t N;
    fin >> forward >> N;

    PathVector path(N);
    for (std::size_t i = 0; i < N; ++i)
      path[i] = Waypoint::read(fin);

    return Path(path, forward);
  }
};

#endif // PURE_PURSUIT_5327K_PATH_H
