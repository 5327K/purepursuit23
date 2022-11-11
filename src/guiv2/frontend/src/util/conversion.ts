export const pxToMM = (px: number, fieldSize: number) => {
  return (px / (fieldSize / 2)) * 1800 - 1800;
};

export const mmToPX = (mm: number, fieldSize: number) => {
  return ((mm + 1800) * (fieldSize / 2)) / 1800;
};

export const clamp = (val: number, min: number, max: number) => {
  return Math.min(Math.max(val, min), max);
}

export const round = (val: number, decimals: number=0) => {
  const mult = Math.pow(10, decimals);
  return Math.round(val * mult) / mult;
}