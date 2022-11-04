const InputField = ({
  htmlFor,
  disabled=false,
}: {
  htmlFor: string;
  disabled?: boolean;
}) => {
  return (
    <>
      <label
        htmlFor={htmlFor}
        className="block text-lg font-medium text-gray-300"
      >
        X:
      </label>
      <input
        type="text"
        className="disabled:cursor-not-allowed text-center text-sm rounded-lg block w-16 p-2.5 bg-gray-700 disabled:bg-gray-800 border-gray-600 text-white"
        disabled={false}
        required
      />
    </>
  );
};

export default InputField;
