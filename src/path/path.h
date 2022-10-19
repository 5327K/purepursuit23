#ifndef PURE_PURSUIT_5327K_PATH_H
#define PURE_PURSUIT_5327K_PATH_H

#include <vector>
#include <array>
#include <algorithm>
#include <sstream>
#include <fstream>

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

#pragma endregion
};

#endif // PURE_PURSUIT_5327K_PATH_H
