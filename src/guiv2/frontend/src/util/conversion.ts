export const pxToMM = (px: number, fieldSize: number) => {
  return (px / (fieldSize / 2)) * 1800;
};

export const mmToPX = (mm: number, fieldSize: number) => {
  return (mm * (fieldSize / 2)) / 1800;
};

export const mmToCanvas = (x: number, y: number, fieldSize: number) => {
  return {
    x: mmToPX(x, fieldSize) + fieldSize / 2,
    y: -mmToPX(y, fieldSize) + fieldSize / 2,
  };
};

export const canvasToMM = (rawX: number, rawY: number, field: HTMLCanvasElement) => {
  const fieldLeft = field.offsetLeft + field.clientLeft,
    fieldTop = field.offsetTop + field.clientTop;

  const fieldSize = field.clientWidth;
  const actualFieldSize = field.offsetWidth;

  const normX = (rawX - fieldLeft) / actualFieldSize,
    normY = (rawY - fieldTop) / actualFieldSize;

  const x = normX * fieldSize - fieldSize / 2,
    y = -(normY * fieldSize - fieldSize / 2);

  return { x: pxToMM(x, fieldSize), y: pxToMM(y, fieldSize) };
};