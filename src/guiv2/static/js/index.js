const fieldImagePath = "/static/images/field-full.png";

const fieldImage = new Image();
fieldImage.src = fieldImagePath;

const field = document.getElementById("field");
const fieldSize = parseInt(field.getAttribute("width"));
const fieldCtx = field.getContext("2d");

const xInput = document.getElementById("xValue"),
  yInput = document.getElementById("yValue");

const radius = 10;

let selected = -1;
let mouseDown = false;
const points = [];

const pxToMM = (px) => {
  return (px / (fieldSize / 2)) * 1800;
};

const mmToPX = (mm) => {
  return (mm * (fieldSize / 2)) / 1800;
};

const mmToCanvas = (x, y) => {
  return {
    x: mmToPX(x) + fieldSize / 2,
    y: -mmToPX(y) + fieldSize / 2,
  };
};

const canvasToMM = (rawX, rawY) => {
  const fieldLeft = field.offsetLeft + field.clientLeft,
    fieldTop = field.offsetTop + field.clientTop;

  const actualFieldSize = field.offsetWidth;

  const normX = (rawX - fieldLeft) / actualFieldSize,
    normY = (rawY - fieldTop) / actualFieldSize;

  const x = normX * fieldSize - fieldSize / 2,
    y = -(normY * fieldSize - fieldSize / 2);

  return { x: pxToMM(x), y: pxToMM(y) };
};

const draw = () => {
  // Draw background image
  fieldCtx.drawImage(fieldImage, 0, 0, fieldSize, fieldSize);

  // #region Draw all draggable points
  fieldCtx.fillStyle = "red";
  for (let i = 0; i < points.length; ++i) {
    const point = points[i];
    const { x, y } = mmToCanvas(point.x, point.y);

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

field.addEventListener("mousedown", (e) => {
  mouseDown = true;
  const { x, y } = canvasToMM(e.x, e.y);

  let found = false;
  for (let i = 0; i < points.length; ++i) {
    if (
      x - pxToMM(radius) <= points[i].x &&
      points[i].x <= x + pxToMM(radius) &&
      y - pxToMM(radius) <= points[i].y &&
      points[i].y <= y + pxToMM(radius)
    ) {
      found = true;
      selected = i;
      break;
    }
  }

  if (!found) selected = points.push({ x, y }) - 1;
});

// Drag selected point on mouse move
field.addEventListener("mousemove", (e) => {
  if (mouseDown && selected != -1) {
    const { x, y } = canvasToMM(e.x, e.y);

    points[selected].x = x;
    points[selected].y = y;
  }
})

field.addEventListener("mouseup", (e) => {
  mouseDown = false;
});

const mainLoop = () => {
  draw();
  requestAnimationFrame(mainLoop);
};

requestAnimationFrame(mainLoop);
