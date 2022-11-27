#include "main.h"

#include "purepursuit/purepursuit.h"

PurePursuit::TickData PurePursuit::tick(const Path &path)
{
  const auto wheelV = driveTrain.getWheelVelocities();
  const pros::c::gps_status_s_t pos = driveTrain.getGPSSensorData();
  const Waypoint posWaypoint = {pos.x, pos.y};

  TickData data;

  const std::size_t closestPointI = PurePursuit::PurePursuitUtil::getClosestPointIndex(path, posWaypoint);
  const auto [lookaheadPt, isEnd] = PurePursuitUtil::getLookaheadPoint(path, posWaypoint, lookaheadDistance, closestPointI);
  data.lookaheadPt = lookaheadPt;

  const double velocity = path.path[closestPointI].targetV;
  data.curvature = PurePursuitUtil::calculateCurvatureOfArc(path, posWaypoint, pos.yaw, lookaheadPt, lookaheadDistance);
  double leftV = PurePursuitUtil::calculateLeftWheelTargetVelocity(velocity, robotTrack, data.curvature, stuckVel);
  double rightV = PurePursuitUtil::calculateRightWheelTargetVelocity(velocity, robotTrack, data.curvature, stuckVel);

  if (!path.forward)
  {
    leftV = -leftV;
    rightV = -rightV;
  }

  const double leftFeedback = feedbackMultiplier * (leftV - wheelV.first);
  const double rightFeedback = feedbackMultiplier * (rightV - wheelV.second);

  driveTrain.setVelocities(leftV + leftFeedback, rightV + rightFeedback);

  std::cout << leftV + leftFeedback << ' ' << rightV + rightFeedback << '\n';

  data.ended = closestPointI == path.path.size() - 1;
  return data;
}

void PurePursuit::follow(const Path &path)
{
  // TODO: https://pros.cs.purdue.edu/v5/api/cpp/motors.html#get-actual-velocity ?

  while (true)
  {
    if (tick(path).ended)
      break;
  }
}
