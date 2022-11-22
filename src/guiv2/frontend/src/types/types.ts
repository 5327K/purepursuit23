export interface Point {
  x: number;
  y: number;
};

export interface Waypoint {
  x: number;
  y: number;
  dist: number;
  curvature: number;
  targetV: number;
}
