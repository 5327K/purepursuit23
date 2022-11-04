import { useEffect, useRef, useState } from "react";

import Konva from "konva";
import {
  Circle,
  Image as KonvaImage,
  KonvaNodeComponent,
  Layer,
  Stage,
  StageProps,
} from "react-konva";

import fieldImagePath from "../assets/field-full.png";

const CanvasPoint = () => {
  return <Circle />;
};

const Field = () => {
  const wrapper = useRef<HTMLDivElement | null>(null);
  const [stage, setStage] = useState<Konva.Stage | null>(null);
  const [fieldSize, setFieldSize] = useState(1000);

  const fieldImage = new Image();
  fieldImage.src = fieldImagePath;

  useEffect(() => {
    if (!wrapper?.current) return;

    console.log(fieldSize);

    const onResize = () => {
      if (!wrapper?.current || !stage) return;

      const newFieldSize = Math.min(
        wrapper.current.clientWidth,
        wrapper.current.clientHeight
      );

      stage.width(newFieldSize);
      stage.height(newFieldSize);
      setFieldSize(newFieldSize);
      console.log(newFieldSize);
    };

    const resizeObserver = new ResizeObserver(onResize);
    resizeObserver.observe(wrapper.current);

    onResize();

    return () => {
      resizeObserver.disconnect();
    };
  }, [stage, fieldSize]);

  return (
    <div
      className="inline-block relative max-w-full max-h-full min-w-[200px] min-h-[200px] grow basis-auto shrink aspect-square"
      ref={wrapper}
    >
      <Stage ref={(ref) => setStage(ref)} className="absolute">
        <Layer>
          <KonvaImage
            image={fieldImage}
            width={fieldSize}
            height={fieldSize}
          />
        </Layer>
      </Stage>
    </div>

    /*<canvas
      id="field"
      width="1000"
      height="1000"
      className="block h-auto w-auto max-w-full max-h-full basis-auto m-0"
    ></canvas>*/
  );
};

export default Field;
