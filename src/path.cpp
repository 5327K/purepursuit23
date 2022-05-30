#include "path.h"

#include <vector>
#include <cmath>

constexpr void Path::injectPoints()
{

}

constexpr void Path::calcDistances()
{
  double dist = 0;
  this->path[0].dist = 0;
  for (int i = 1; i < path.size(); ++i)
  {
    // dist_i = dist_i-1 + distance between points i - 1 and i
    this->path[i].dist = this->path[i - 1].dist +
                         std::sqrt(this->path[i].x * this->path[i].x +
                                   this->path[i].y * this->path[i].y);
  }
}
