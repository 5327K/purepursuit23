import { useContext, useEffect, useState } from "react";
import { ApiContext } from "../App";
import { Point, Waypoint } from "../types/types";

const usePath = (points: Point[]) => {
  const [path, setPath] = useState<Waypoint[] | null>(null);
  const api = useContext(ApiContext);

  // TODO: remove hardcoding of attributes apart from `points`
  useEffect(() => {
    if (!api.isConnected()) return;

    console.log("sending request");
    api.pathUpdated(true, 110, 20, 3, points);
  }, [points]);

  useEffect(() => {
    api.onopen.push(() => {
      api.pathUpdated(true, 110, 20, 3, points);
    });

    api.callbacks["updated-path"].push((msg) => {
      const lines = msg.split("\n");

      const line1 = lines[0].split(" ");
      const N = parseInt(line1[1]);

      const pts: Waypoint[] = [];
      for (let i = 0; i < N; ++i) {
        const line = lines[i + 1].split(" ");

        pts.push({
          x: parseFloat(line[0]),
          y: parseFloat(line[1]),
          targetV: parseFloat(line[2])
        });
      }

      console.log(pts);

      setPath(pts);
    });
  }, []);

  return path;
};

export default usePath;
