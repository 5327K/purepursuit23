import { useState } from "react";

const InputField = ({
  label,
  initialValue,
  onValueChange,
  disabled=false,
}: {
  label: string;
  initialValue: string;
  onValueChange: (value: string) => void;
  disabled?: boolean;
}) => {
  const [value, setValue] = useState<string>(initialValue);

  return (
    <>
      <label
        className="block text-lg font-medium text-gray-300"
      >
        {label}
      </label>

      <input
        type="text"
        className="disabled:cursor-not-allowed text-center text-sm rounded-lg block w-16 p-2.5 bg-gray-700 disabled:bg-gray-800 border-gray-600 text-white"
        disabled={false}
        value={value}
        onChange={(e) => {
          setValue(e.target.value);
          onValueChange(value);
        }}
      />
    </>
  );
};

export default InputField;
