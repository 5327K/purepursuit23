export interface Point {
  x: number;
  y: number;
};

export interface Waypoint {
  x: number;
  y: number;
  targetV: number;
}

export interface RobotState {
  x: number;
  y: number;
  yaw: number;
  velL: number;
  velR: number;
}

export interface VisData {
  x: number;
  y: number;
  curvature: number;
}
