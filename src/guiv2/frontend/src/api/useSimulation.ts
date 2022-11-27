import { useContext, useEffect, useState } from "react";
import { ApiContext } from "../App";
import { Point, RobotState, VisData } from "../types/types";

const useSimulation = (
  points: Point[]
): [RobotState[], VisData | null, boolean, () => void] => {
  const api = useContext(ApiContext);
  const [simulationRunning, setSimulationRunning] = useState<boolean>(false);
  const [simulatedPath, setSimulatedPath] = useState<RobotState[]>([]);
  const [visData, setVisData] = useState<VisData | null>(null);

  // invalidate current simulated path whenever points change
  useEffect(() => {
    setSimulatedPath([]);
    setVisData(null);
  }, [points]);

  useEffect(() => {
    api.callbacks["simulation-part"].push((msg) => {
      console.log(msg);
      const lines = msg.split("\n");
      const line1 = lines[0].split(" ");
      const line2 = lines[1].split(" ");
      const line3 = lines[2].split(" ");

      const idx = parseInt(line1[1]);
      console.log(simulatedPath);
      let simulatedPathCopy = simulatedPath.slice();
      simulatedPathCopy.splice(idx, 0, {
        x: parseFloat(line2[0]),
        y: parseFloat(line2[1]),
        yaw: parseFloat(line2[2]),
        velL: parseFloat(line2[3]),
        velR: parseFloat(line2[4]),
      });
      setSimulatedPath(simulatedPathCopy);

      setVisData({
        x: parseFloat(line3[0]),
        y: parseFloat(line3[1]),
        curvature: parseFloat(line3[3]),
      });
    });

    api.callbacks["simulation-end"].push((msg) => {
      console.log(msg);
      setSimulationRunning(false);
    });
  }, []);

  useEffect(() => {
    console.log(simulatedPath);
  }, [simulatedPath]);

  const toggleSimulation = () => {
    if (simulationRunning) {
      //alert("This has not been implemented yet!");
      api.cancelSimulation();
    } else {
      setSimulationRunning(true);
      api.startSimulation();
    }
  };

  return [simulatedPath, visData, simulationRunning, toggleSimulation];
};

export default useSimulation;
