import { useEffect, useRef, useState } from "react";

import Konva from "konva";
import { Image as KonvaImage, Layer, Stage } from "react-konva";

import fieldImagePath from "../assets/field-full.png";
import { Point } from "../types/types";
import InputField from "./InputField";
import CanvasPoint from "./CanvasPoint";
import usePath from "../api/usePath";
import Api from "../api/api";

const Field = () => {
  const wrapper = useRef<HTMLDivElement | null>(null);
  const [stage, setStage] = useState<Konva.Stage | null>(null);
  const [fieldSize, setFieldSize] = useState<number>(1000);

  const [points, setPoints] = useState<Point[]>([{ x: 0, y: 0.2 }]);
  const [selected, setSelected] = useState<number | null>(null);

  const path = usePath(points);

  const fieldImage = new Image();
  fieldImage.src = fieldImagePath;

  useEffect(() => {
    if (!wrapper?.current) return;

    const onResize = () => {
      if (!wrapper?.current || !stage) return;

      const newFieldSize =
        Math.min(wrapper.current.clientWidth, wrapper.current.clientHeight) -
        20;

      stage.width(newFieldSize);
      stage.height(newFieldSize);
      setFieldSize(newFieldSize);
    };

    const resizeObserver = new ResizeObserver(onResize);
    resizeObserver.observe(wrapper.current);

    onResize();

    return () => {
      resizeObserver.disconnect();
    };
  }, [stage, fieldSize]);

  useEffect(() => {
    console.log(points);
  }, [points]);

  return (
    <div
      className="inline-block relative max-w-full max-h-full min-w-[200px] min-h-[200px] grow aspect-square"
      ref={wrapper}
    >
      <div className="absolute top-1/2 translate-y-[-50%] flex flex-col space-y-5">
        <Stage ref={(ref) => setStage(ref)}>
          <Layer>
            {/* TODO: Add darkness to background to make it easier to see */}
            <KonvaImage
              image={fieldImage}
              width={fieldSize}
              height={fieldSize}
            />
            {points.map((_, idx) => {
              return (
                <CanvasPoint
                  fieldSize={fieldSize}
                  key={`draggable-point-${idx}`}
                  index={idx}
                  points={points}
                  setPoints={setPoints}
                  selected={selected}
                  setSelected={setSelected}
                />
              );
            })}
          </Layer>
        </Stage>

        <div className="w-full flex flex-row items-center justify-evenly space-x-2">
          <div className="flex flex-row space-x-2 items-center">
            <InputField
              label="X:"
              value={selected !== null ? points[selected].x.toFixed(4) : ""}
              setValue={(value) => {
                if (!selected) return;
                const copy = points.slice();
                copy[selected].x = parseFloat(value);
                setPoints(copy);
              }}
              disabled={selected === null}
            />
            <p className="block text-md md:text-lg text-gray-300">m</p>
          </div>
          <div className="flex flex-row space-x-2 items-center">
            <InputField
              label="Y:"
              value={selected !== null ? points[selected].y.toFixed(4) : ""}
              setValue={(value) => {
                if (!selected) return;
                const copy = points.slice();
                copy[selected].y = parseFloat(value);
                setPoints(copy);
              }}
              disabled={selected === null}
            />
            <p className="block text-md md:text-lg text-gray-300">m</p>
          </div>
        </div>
      </div>
    </div>
  );
};

export default Field;
