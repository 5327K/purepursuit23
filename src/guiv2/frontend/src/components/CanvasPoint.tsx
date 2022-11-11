import { Circle } from "react-konva";
import { Point } from "../types/types";
import { clamp, mmToPX, pxToMM, round } from "../util/conversion";

const CanvasPoint = ({
  fieldSize,
  index,
  points,
  setPoints,
  selected,
  setSelected,
}: {
  index: number;
  fieldSize: number;
  selected: number | null;
  setSelected: (selected: number | null) => void;
  points: Point[];
  setPoints: (points: Point[]) => void;
}) => {
  return (
    <Circle
      radius={fieldSize / 80}
      fill="red"
      stroke={selected === index ? "white" : "black"}
      strokeWidth={selected === index ? fieldSize / 250 : fieldSize / 300}
      x={mmToPX(points[index].x, fieldSize)}
      y={mmToPX(points[index].y, fieldSize)}
      draggable={true}
      dragBoundFunc={(pos) => {
        return {
          x: clamp(pos.x, 0, fieldSize),
          y: clamp(pos.y, 0, fieldSize),
        };
      }}
      onTouchStart={() => setSelected(index)}
      onMouseDown={() => setSelected(index)}
      onDragMove={(evt) => {
        const copy = points.slice();
        copy[index] = {
          x: round(pxToMM(evt.target.attrs.x, fieldSize), 2),
          y: round(pxToMM(evt.target.attrs.y, fieldSize), 2),
        };
        console.log(copy[index]);
        setPoints(copy);
      }}
    />
  );
};

export default CanvasPoint;
