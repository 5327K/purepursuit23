const InputField = ({
  label,
  value,
  setValue,
  disabled = false,
}: {
  label: string;
  value: string | undefined;
  setValue: (value: string) => void;
  disabled?: boolean;
}) => {
  return (
    <>
      <label className="block text-md md:text-lg font-medium text-gray-300">{label}</label>

      <input
        type="text"
        className="disabled:cursor-not-allowed text-center text-xs md:text-sm rounded-lg block w-16 md:w-20 p-2.5 bg-gray-700 disabled:bg-gray-800 border-gray-600 text-white"
        disabled={disabled}
        value={value}
        onChange={(e) => setValue(e.target.value)}
      />
    </>
  );
};

export default InputField;
