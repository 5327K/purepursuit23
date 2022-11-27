import { Circle } from "react-konva";
import { Point } from "../types/types";
import { clamp, mToPX, pxToM, round } from "../util/conversion";

const CanvasPoint = ({
  fieldSize,
  index,
  points,
  setPoints,
  selected,
  setSelected,
  draggable
}: {
  index: number;
  fieldSize: number;
  selected: number | null;
  setSelected: (selected: number | null) => void;
  points: Point[];
  setPoints: (points: Point[]) => void;
  draggable: boolean
}) => {
  return (
    <Circle
      radius={index === 0 || index === points.length - 1 ? fieldSize / 80 : fieldSize / 90}
      fill={!draggable ? "rgb(82 82 91)" : (index === 0 ? "rgb(34 197 94)" : (index === points.length - 1 ? "red" : "rgb(234 179 8)"))}
      stroke={draggable && selected === index ? "yellow" : "white"}
      strokeWidth={draggable && selected === index ? fieldSize / 250 : fieldSize / 300}
      x={mToPX(points[index].x, fieldSize)}
      y={mToPX(-points[index].y, fieldSize)}
      draggable={draggable}
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
          x: round(pxToM(evt.target.attrs.x, fieldSize), 4),
          y: round(-pxToM(evt.target.attrs.y, fieldSize), 4),
        };
        console.log(copy[index]);
        setPoints(copy);
      }}
    />
  );
};

export default CanvasPoint;
