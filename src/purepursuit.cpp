#include "main.h"

#include "purepursuit/purepursuit.h"

bool PurePursuit::tick(const Path &path, int &closestPt)
{
  const auto wheelV = driveTrain.getWheelVelocities();
  const pros::c::gps_status_s_t pos = driveTrain.getGPSSensorData();
  const Waypoint posWaypoint = {pos.x, pos.y};

  std::cout << "gps: " << pos.x << ' ' << pos.y << '\n';

  closestPt = PurePursuitUtil::getClosestPointIndex(path, posWaypoint, closestPt);
  const auto [lookaheadPt, isEnd] = PurePursuitUtil::getLookaheadPoint(path, posWaypoint, lookaheadDistance, closestPt);
  std::cout << "lookahead: " << lookaheadPt << '\n';

  const double velocity = path.path[closestPt].targetV;
  const double curvature = PurePursuitUtil::calculateCurvatureOfArc(path, posWaypoint, pos.yaw, lookaheadPt, lookaheadDistance);
  double leftV = PurePursuitUtil::calculateLeftWheelTargetVelocity(velocity, robotTrack, curvature);
  double rightV = PurePursuitUtil::calculateRightWheelTargetVelocity(velocity, robotTrack, curvature);

  // std::cout << "actual wheel velocities: " << wheelV.first << ' ' << wheelV.second << '\n';
  // std::cout << "target wheel velocities: " << leftV << ' ' << rightV << '\n';

  if (!path.forward)
  {
    leftV = -leftV;
    rightV = -rightV;
  }

  const double leftFeedback = feedbackMultiplier * (leftV - wheelV.first);
  const double rightFeedback = feedbackMultiplier * (rightV - wheelV.second);

  driveTrain.setVelocities(leftV + leftFeedback, rightV + rightFeedback);

  const auto &lastPt = path.path[path.path.size() - 1];
  return isEnd && std::abs(pos.x - lastPt.x) <= 0.01 && std::abs(pos.x - lastPt.x) <= 0.01;
}

void PurePursuit::follow(const Path &path)
{
  int closestPt = 0;

  // TODO: https://pros.cs.purdue.edu/v5/api/cpp/motors.html#get-actual-velocity ?

  while (true)
  {
    if (tick(path, closestPt))
      break;
  }
}
