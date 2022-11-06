import { useContext, useEffect, useState } from "react";
import { ApiContext } from "../App";
import { Point } from "../types/types";

const usePath = (points: Point[]) => {
  const [path, setPath] = useState<Point[] | null>(null);
  const api = useContext(ApiContext);

  useEffect(() => {
    if (!api.isConnected()) return;

    console.log("sending request");
    api.pathUpdated(points);
  }, [points]);

  useEffect(() => {
    api.onopen.push(() => {
      api.pathUpdated(points);
    });

    api.callbacks["updated-path"].push((tokens) => {
      console.log(tokens);
    });
  }, []);

  return path;
};

export default usePath;
