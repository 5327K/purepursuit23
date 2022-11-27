import { Circle, Rect } from "react-konva";
import { RobotState, VisData } from "../types/types";
import { mToPX } from "../util/conversion";

const Robot = ({
  robotState,
  visData,
  fieldSize,
}: {
  robotState: RobotState;
  visData: VisData;
  fieldSize: number;
}) => {
  return (
    <>
      <Rect
        x={mToPX(robotState.x, fieldSize)}
        y={mToPX(-robotState.y, fieldSize)}
        offsetX={25}
        offsetY={25}
        rotation={(robotState.yaw / Math.PI) * 180}
        width={50}
        height={50}
        stroke="black"
        fill="black"
        opacity={0.8}
      />

      <Circle
        x={mToPX(robotState.x, fieldSize)}
        y={mToPX(-robotState.y, fieldSize)}
        radius={8}
        fill="orange"
      />

      <Rect
        x={mToPX(robotState.x, fieldSize)}
        y={mToPX(-robotState.y, fieldSize)}
        offsetX={26}
        offsetY={25}
        rotation={(robotState.yaw / Math.PI) * 180}
        width={2}
        height={(-robotState.velL / 100) * 30} // TODO: rmoeve hardcoded velocity
        fill="red"
      />

      <Rect
        x={mToPX(robotState.x, fieldSize)}
        y={mToPX(-robotState.y, fieldSize)}
        offsetX={-23}
        offsetY={25}
        rotation={(robotState.yaw / Math.PI) * 180}
        width={2}
        height={(-robotState.velR / 100) * 30} // TODO: rmoeve hardcoded velocity
        fill="red"
      />
    </>
  );
};

export default Robot;
