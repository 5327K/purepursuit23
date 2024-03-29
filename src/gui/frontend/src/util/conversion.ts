export const pxToM = (px: number, fieldSize: number) => {
  return (px / (fieldSize / 2)) * 180 - 180;
};

export const mToPX = (m: number, fieldSize: number) => {
  return ((m + 180) * (fieldSize / 2)) / 180;
};

export const clamp = (val: number, min: number, max: number) => {
  return Math.min(Math.max(val, min), max);
}

export const round = (val: number, decimals: number=0) => {
  const mult = Math.pow(10, decimals);
  return Math.round(val * mult) / mult;
}