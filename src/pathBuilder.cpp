#include "pathBuilder.h"
#include "path.h"

#include <vector>

constexpr PathBuilder &PathBuilder::addPoint(Waypoint point)
{
  this->path.push_back(point);
  return *this;
}

constexpr PathBuilder &PathBuilder::addPoints(std::vector<Waypoint> points)
{
  this->path.insert(this->path.end(), points.begin(), points.end());
  return *this;
}

constexpr std::vector<Waypoint> PathBuilder::injectPoints(Waypoint start, Waypoint end)
{

}

constexpr Path PathBuilder::build()
{
  std::vector<Waypoint> path;
  for (int i = 0; i < this->path.size() - 1; ++i)
  {
    std::vector<Waypoint> tmp = this->injectPoints(this->path[i], this->path[i + 1]);
    path.insert(path.end(), tmp.begin(), tmp.end());
  }

  return Path(path, this->forward);
}
