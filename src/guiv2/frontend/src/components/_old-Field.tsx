import { useEffect, useRef, useState } from "react";

import { Point } from "../types/types";
import { canvasToMM, mmToCanvas, pxToMM } from "../util/conversion";

import fieldImagePath from "../assets/field-full.png";

const radius = 10;

const draw = (
  fieldImage: HTMLImageElement,
  fieldCtx: CanvasRenderingContext2D,
  fieldSize: number,
  selected: number | null,
  points: Point[]
) => {
  // Draw background image
  fieldCtx.drawImage(fieldImage, 0, 0, fieldSize, fieldSize);

  // #region Draw all draggable points
  fieldCtx.fillStyle = "red";
  for (let i = 0; i < points.length; ++i) {
    const point = points[i];
    const { x, y } = mmToCanvas(point.x, point.y, fieldSize);
    console.log(fieldSize);

    // Draw the point itself
    fieldCtx.beginPath();
    fieldCtx.arc(x, y, radius, 0, 2 * Math.PI, false);
    fieldCtx.fill();

    // Draw the stroke around the point (white if selected, black if not)
    if (selected === i) {
      fieldCtx.lineWidth = 3;
      fieldCtx.strokeStyle = "white";
    } else {
      fieldCtx.lineWidth = 2;
      fieldCtx.strokeStyle = "black";
    }
    fieldCtx.stroke();
  }
  // #endregion
};

const Field = () => {
  const field = useRef<HTMLCanvasElement | null>(null);
  const [selected, setSelected] = useState<number | null>(null);
  const [points, setPoints] = useState<Point[]>([]);

  let mousedown = false;

  const onMousedown = (e: MouseEvent): void => {
    if (!field?.current) return;
    const fieldSize = field.current?.clientWidth;
    mousedown = true;

    if (!field?.current) return;
    const { x, y } = canvasToMM(e.x, e.y, field.current);
    console.log(x, y);

    let found = false;
    for (let i = 0; i < points.length; ++i) {
      if (
        x - pxToMM(radius, fieldSize) <= points[i].x &&
        points[i].x <= x + pxToMM(radius, fieldSize) &&
        y - pxToMM(radius, fieldSize) <= points[i].y &&
        points[i].y <= y + pxToMM(radius, fieldSize)
      ) {
        found = true;
        setSelected(i);
        break;
      }
    }

    if (!found) {
      setPoints([...points, { x, y }]);
      setSelected(points.length - 1);
    }
  };

  const onMousemove = (e: MouseEvent): void => {
    if (!field?.current) return;
    if (mousedown && selected !== null) {
      const { x, y } = canvasToMM(e.x, e.y, field.current);

      points[selected].x = x;
      points[selected].y = y;

      setPoints(points);
    }
  };

  const onMouseup = (e: MouseEvent): void => {
    mousedown = false;
  };

  useEffect(() => {
    if (!field?.current) return;

    field.current.addEventListener("mousedown", onMousedown);
    field.current.addEventListener("mousemove", onMousemove);
    field.current.addEventListener("mouseup", onMouseup);

    const fieldCtx = field.current.getContext("2d");
    if (!fieldCtx) return;

    const fieldImage = new Image();
    fieldImage.src = fieldImagePath;

    const mainLoop = () => {
      if (!field?.current) return;
      console.log(field.current.offsetWidth, field.current.clientWidth)
      draw(fieldImage, fieldCtx, field.current.offsetWidth, selected, points);
      requestAnimationFrame(mainLoop);
    };

    fieldImage.onload = () => {
      requestAnimationFrame(mainLoop);
    };

    return () => {
      if (!field?.current) return;
      field.current.removeEventListener("mousedown", onMousedown);
      field.current.removeEventListener("mousemove", onMousemove);
      field.current.removeEventListener("mouseup", onMouseup);
    };
  }, []);

  return (
    <canvas
      id="field"
      width="1000"
      height="1000"
      className="block h-auto w-auto max-w-full max-h-full basis-auto m-0"
      ref={field}
    ></canvas>
  );
};

export default Field;
