import { Circle } from "react-konva";
import { RobotState, VisData } from "../types/types";
import { mToPX } from "../util/conversion";
import intersection from "../util/intersection";

const CurvatureCircle = ({
  robotState,
  visData,
  fieldSize,
}: {
  robotState: RobotState;
  visData: VisData;
  fieldSize: number;
}) => {
  const r = 1 / Math.abs(visData.curvature);
  const intersect = intersection(robotState.x, robotState.y, r, visData.x, visData.y, r);

  const pt = Math.sign(visData.curvature) === 1 ? 1 : 0;

  return intersect ? (
    <Circle
      x={mToPX(intersect[pt], fieldSize)}
      y={mToPX(-intersect[pt + 2], fieldSize)}
      radius={(Math.abs(r) / 360) * fieldSize}
      stroke="yellow"
    />
  ) : (
    <></>
  );
};

export default CurvatureCircle;
