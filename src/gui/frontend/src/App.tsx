import { createContext, useState, Context } from "react";
import Api from "./api/api";
import Alert from "./components/Alert";
import Field from "./components/Field";
import { RobotState } from "./types/types";
import lookaheadPath from "./assets/lookahead.png";

const api = new Api();
export const ApiContext = createContext(api);

// TODO: make alert work

const App = () => {
  const [stateData, setStateData] = useState<RobotState>({
    x: 0,
    y: 0,
    yaw: 0,
    velL: 0,
    velR: 0,
  });

  return (
    <ApiContext.Provider value={api}>
      <div className="w-full h-full max-h-full bg-black p-8 flex flex-col space-y-5">
        {/* <Alert>HELP ME</Alert> */}

        <div className="flex flex-col justify-center items-center grow shrink">
          <div className="flex flex-row space-x-2 md:w-[800px] sm:w-[600px] w-[400px] grow shrink">
            <div className="flex flex-col justify-center items-center space-y-5 w-7/12">
              <Field setStateData={setStateData} />
            </div>
            <div className="flex flex-col w-5/12 grow shrink bg-gray-700 rounded-xl p-4 pt-8">
              <h1 className="text-3xl text-yellow-500 text-center">
                5327K's Adaptive Pure Pursuit Controller
              </h1>
              <br />
              {stateData && (
                <div className="flex align space-x-2 justify-center">
                  <div className="flex flex-col">
                    <p className="text-white font-bold text-right">
                      Robot Position X :
                    </p>
                    <p className="text-white font-bold text-right">
                      Robot Position Y :
                    </p>
                    <br />
                    <p className="text-white font-bold text-right">
                      Robot Direction (Yaw) :
                    </p>
                    <br />
                    <p className="text-white font-bold text-right">
                      Left Wheel Velocity :
                    </p>
                    <p className="text-white font-bold text-right">
                      Right Wheel Velocity :
                    </p>
                  </div>
                  <div className="flex flex-col">
                    <p className="text-green-500 font-bold">
                      {stateData.x.toFixed(2)}{" "}
                      <span className="text-gray-400">cm</span>
                    </p>
                    <p className="text-green-500 font-bold">
                      {stateData.y.toFixed(2)}{" "}
                      <span className="text-gray-400">cm</span>
                    </p>
                    <br />
                    <p className="text-green-500 font-bold">
                      {stateData.yaw.toFixed(2)}{" "}
                      <span className="text-gray-400">rad</span>
                    </p>
                    <br />

                    <p className="text-green-500 font-bold">
                      {stateData.velL.toFixed(2)}{" "}
                      <span className="text-gray-400">cm/s</span>
                    </p>
                    <p className="text-green-500 font-bold">
                      {stateData.velR.toFixed(2)}{" "}
                      <span className="text-gray-400">cm/s</span>
                    </p>
                  </div>
                </div>
              )}

              <br />
              <hr className="border-dashed" />
              <br />

              <p className="text-white mb-4">
                Pure Pursuit is an algorithm that uses advanced{" "}
                <span className="text-teal-500 font-bold">
                  geometric and trignometric
                </span>{" "}
                math, allowing a robot to{" "}
                <span className="text-teal-500 font-bold">autonomously</span>{" "}
                follow a path efficiently.
              </p>

              <p className="ml-4 mb-2 text-white text-sm">
                <span className="text-white font-bold">A)</span> Finds closest
                point to robot on path for it to target (aka the <span className="text-teal-500 font-bold">lookahead
                point</span>).
              </p>
              <p className="ml-4 mb-2 text-white text-sm">
                <span className="text-white font-bold">B)</span> Calculates the
                optimal <span className="text-teal-500 font-bold">curvature</span> for the robot to turn to reach the lookahead
                point.
              </p>
              <p className="ml-4 mb-2 text-white text-sm">
                <span className="text-white font-bold">C)</span> Computes the
                velocities of the left and right wheels using the{" "}
                <span className="text-teal-500 font-bold">
                  skid steer kinematic model
                </span>
                .
              </p>
            </div>
          </div>
        </div>
      </div>
    </ApiContext.Provider>
  );
};

export default App;
