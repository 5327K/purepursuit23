#ifndef PURE_PURSUIT_5327K_PATH_H
#define PURE_PURSUIT_5327K_PATH_H

#include <vector>
#include <array>
#include <algorithm>
#include <sstream>
#include <istream>

#include "waypoint.h"

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

#pragma region File / String Input & Output

  friend std::ostream &operator<<(std::ostream &os, const Path &p)
  {
    os << p.forward << ' ' << p.path.size() << '\n';
    for (const Waypoint &point : p.path)
      os << point << '\n';

    return os;
  }

  /* Returns the string representation of a Path, used for saving a path for later use. */
  std::string toString() const
  {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
  }

  /* Reads the Path::toString representation of a Path and returns the Path object
     associated with it. */
  static Path read(std::istream &s)
  {
    bool forward;
    std::size_t N;
    s >> forward >> N;

    PathVector path(N);
    for (std::size_t i = 0; i < N; ++i)
      path[i] = Waypoint::read(s);

    return Path(path, forward);
  }

#pragma endregion
};

#endif // PURE_PURSUIT_5327K_PATH_H
