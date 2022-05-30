#ifndef PURE_PURSUIT_5327K_PATH_BUILDER_H
#define PURE_PURSUIT_5327K_PATH_BUILDER_H

#include "path.h"

class PathBuilder
{
private:
  std::vector<Waypoint> path;
  bool forward;

  constexpr std::vector<Waypoint> injectPoints(Waypoint start, Waypoint end);
  
  constexpr void smooth(Path &path);

  constexpr void setCurvatures(Path &path);
  constexpr void setDistances(Path &path);
  constexpr void setTargetVel(Path &path);

public:
  constexpr PathBuilder(bool forward): forward(forward) {};

  constexpr PathBuilder& addPoint(Waypoint point);
  constexpr PathBuilder& addPoints(std::vector<Waypoint> points);

  constexpr Path build();
};

#endif // PURE_PURSUIT_5327K_PATH_BUILDER_H
