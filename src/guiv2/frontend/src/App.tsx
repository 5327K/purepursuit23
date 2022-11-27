import { createContext, useState, Context } from "react";
import Api from "./api/api";
import Alert from "./components/Alert";
import Field from "./components/Field";

const api = new Api();
export const ApiContext = createContext(api);

// TODO: make alert work

const App = () => {
  return (
    <ApiContext.Provider value={api}>
      <div className="w-full h-full max-h-full bg-black p-8 flex flex-col space-y-5">
        {/* <Alert>HELP ME</Alert> */}

        <div className="flex flex-col justify-center items-center grow shrink">
          <div className="flex flex-row space-x-2 2xl:w-[1500px] md:w-[800px] sm:w-[600px] w-[400px] grow shrink">
            <div className="flex flex-col justify-center items-center space-y-5 w-8/12">
              <Field />
            </div>
            <div className="flex w-4/12 grow shrink bg-gray-700 rounded-xl p-6">
              <h1 className="text-2xl text-white text-center">
                5327K's Path Planner
              </h1>
            </div>
          </div>
        </div>
      </div>
    </ApiContext.Provider>
  );
};

export default App;
