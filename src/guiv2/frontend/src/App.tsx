import { useState } from "react";
import Field from "./components/Field";
import InputField from "./components/InputField";

const App = () => {
  const [count, setCount] = useState(0);

  return (
    <div className="w-full h-full max-h-full bg-slate-900 p-8 flex flex-col space-y-5">
      <h1 className="text-6xl text-white text-center">5327K's Path Planner</h1>
      <div className="flex flex-col justify-center items-center grow shrink">
        <div className="flex flex-row space-x-2 2xl:w-[1250px] md:w-[700px] sm:w-[500px] w-[400px] grow shrink">
          <div className="flex flex-col justify-center items-center space-y-5 w-8/12">
            <Field />
            <div className="w-full flex flex-row justify-evenly">
              <div className="flex flex-row space-x-2 items-center">
                <InputField htmlFor="xValue" />
                <p className="block text-lg text-gray-300">mm</p>
              </div>
              <div className="flex flex-row space-x-2 items-center">
                <InputField htmlFor="yValue" />
                <p className="block text-lg text-gray-300">mm</p>
              </div>
            </div>
          </div>
          <div className="flex w-4/12 grow shrink bg-gray-700 rounded-xl"></div>
        </div>
      </div>
    </div>
  );
};

export default App;
