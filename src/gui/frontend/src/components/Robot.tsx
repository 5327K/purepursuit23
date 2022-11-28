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
        offsetX={20}
        offsetY={20}
        rotation={(robotState.yaw / Math.PI) * 180}
        width={40}
        height={40}
        stroke="green"
        fill="black"
        opacity={0.8}
      />

      <Rect
        x={mToPX(robotState.x, fieldSize)}
        y={mToPX(-robotState.y, fieldSize)}
        offsetX={21}
        offsetY={20}
        rotation={(robotState.yaw / Math.PI) * 180}
        width={2}
        height={(-robotState.velL / 100) * 50} // TODO: rmoeve hardcoded velocity
        fill="red"
      />

      <Rect
        x={mToPX(robotState.x, fieldSize)}
        y={mToPX(-robotState.y, fieldSize)}
        offsetX={-19}
        offsetY={20}
        rotation={(robotState.yaw / Math.PI) * 180}
        width={2}
        height={(-robotState.velR / 100) * 50} // TODO: rmoeve hardcoded velocity
        fill="red"
      />

      {/* <Circle
        x={mToPX(robotState.x, fieldSize)}
        y={mToPX(-robotState.y, fieldSize)}
        radius={Math.sqrt(2 * 20 * 20)}
        stroke="green"
      /> */}
    </>
  );
};

export default Robot;
