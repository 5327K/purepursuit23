import { useContext, useEffect, useRef, useState } from "react";

import Konva from "konva";
import { Circle, Image as KonvaImage, Layer, Stage } from "react-konva";

import fieldImagePath from "../assets/field-full-bg.png";
import { Point } from "../types/types";
import InputField from "./InputField";
import CanvasPoint from "./CanvasPoint";
import usePath from "../api/usePath";
import { mToPX } from "../util/conversion";
import useSimulation from "../api/useSimulation";
import Robot from "./Robot";
import CurvatureCircle from "./CurvatureCircle";

const Field = () => {
  const wrapper = useRef<HTMLDivElement | null>(null);
  const [stage, setStage] = useState<Konva.Stage | null>(null);
  const [fieldSize, setFieldSize] = useState<number>(1000);

  const [points, setPoints] = useState<Point[]>([
    { x: -121.8898, y: -29.2126 },
    { x: -17.7165, y: 82.0473 },
    { x: 9.9213, y: -88.4252 },
    { x: 106.2992, y: 35.5906 },
  ]);
  const [selected, setSelected] = useState<number | null>(null);

  const path = usePath(points);
  const [simulatedPath, visData, simulationRunning, toggleSimulation] =
    useSimulation(points);

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
        <Stage ref={(ref) => setStage(ref)} className="border-gray-700 border-2">
          <Layer>
            {/* TODO: Add darkness to background to make it easier to see */}
            <KonvaImage
              image={fieldImage}
              width={fieldSize}
              height={fieldSize}
            />

            {simulatedPath.map((pt, idx) => (
              <Circle
                radius={fieldSize / 200}
                fill="black"
                key={idx}
                x={mToPX(pt.x, fieldSize)}
                y={mToPX(-pt.y, fieldSize)}
              />
            ))}

            {path?.map((pt, idx) => (
              <Circle
                radius={fieldSize / 150}
                // TODO: remove hardcoded maxVal
                fill={`rgb(${(1 - pt.targetV / 100) * 255}, 0, ${
                  (pt.targetV / 100) * 255
                })`}
                key={idx}
                x={mToPX(pt.x, fieldSize)}
                y={mToPX(-pt.y, fieldSize)}
              />
            ))}

            {simulatedPath && visData && (
              <Robot
                robotState={simulatedPath[simulatedPath.length - 1]}
                visData={visData}
                fieldSize={fieldSize}
              />
            )}

            {simulatedPath && visData && (
              <CurvatureCircle
                robotState={simulatedPath[simulatedPath.length - 1]}
                visData={visData}
                fieldSize={fieldSize}
              />
            )}

            {visData && (
              <Circle
                radius={fieldSize / 100}
                fill="green"
                x={mToPX(visData.x, fieldSize)}
                y={mToPX(-visData.y, fieldSize)}
              />
            )}

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
                  draggable={!simulationRunning}
                />
              );
            })}
          </Layer>
        </Stage>

        <button
          type="button"
          className={`self-center w-52 text-white focus:ring-4 focus:outline-none font-medium rounded-lg text-sm px-5 py-2.5 text-center inline-flex items-center mr-2 ${
            !simulationRunning
              ? "bg-green-600 hover:bg-green-700 focus:ring-green-800"
              : "bg-red-600 hover:bg-red-700 focus:ring-red-800"
          }`}
          onClick={toggleSimulation}
        >
          {!simulationRunning ? (
            <svg
              xmlns="http://www.w3.org/2000/svg"
              height="30"
              width="30"
              viewBox="0 0 48 48"
              fill="currentColor"
            >
              <path d="M16 37.85v-28l22 14Zm3-14Zm0 8.55 13.45-8.55L19 15.3Z" />
            </svg>
          ) : (
            <svg
              xmlns="http://www.w3.org/2000/svg"
              height="30"
              width="30"
              viewBox="0 0 48 48"
              fill="currentColor"
            >
              <path d="m12.45 37.65-2.1-2.1L21.9 24 10.35 12.45l2.1-2.1L24 21.9l11.55-11.55 2.1 2.1L26.1 24l11.55 11.55-2.1 2.1L24 26.1Z" />
            </svg>
          )}
          <span className="text-center w-full">
            {!simulationRunning ? "Run Simulation" : "Cancel Simulation"}
          </span>
        </button>
      </div>
    </div>
  );
};

export default Field;
