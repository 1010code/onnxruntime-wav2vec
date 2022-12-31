#include <onnxruntime_cxx_api.h>
#include <array>
#include <iostream>

using namespace std;

void getResult(float* floats, int floatsCount) {
	double maxNum = 0;
	int label = 0;
	// pointer array to vector
	vector<double> values(floats, floats + floatsCount);
	// range-based for-loop
	for (int i = 0; i < floatsCount; i++) {
		double prob = values[i];
		std::cout << prob << " ";
		if (prob > maxNum) {
			maxNum = prob;
			label = i;
		}
	}
	std::cout << "\nPredict Label:" << label << "\n";
}

int main()
{
	// gives access to the underlying API (you can optionally customize log)
	// you can create one environment per process (each environment manages an internal thread pool)
	Ort::Env env;

	// creates an inference session for a certain model
	Ort::Session session{ env, "./data/tf_model.onnx", Ort::SessionOptions{} };

	// Ort::Session gives access to input and output information:
	// - count
	// - name
	// - shape and type
	/*std::cout << "Number of model inputs: " << session.GetInputCount() << "\n";
	std::cout << "Number of model outputs: " << session.GetOutputCount() << "\n";*/

	// you can customize how allocation works. Let's just use a default allocator provided by the library
	Ort::AllocatorWithDefaultOptions allocator;
	// get input and output names
	auto* inputName = session.GetInputName(0, allocator);
	std::cout << "Input name: " << inputName << "\n";

	auto* outputName = session.GetOutputName(0, allocator);
	std::cout << "Output name: " << outputName << "\n";

	// get input shape
	auto inputShape = session.GetInputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape();
	/*std::cout << "inputShape size: " << inputShape.size() << "\n";
	std::cout << "inputShape data:" << inputShape.data() << "\n";*/
	// set some input values
	std::vector<float> inputValues = { 6.7, 3.1, 4.4, 1.4 };
	std::cout << "inputValues size: " << inputValues.size() << "\n";
	std::cout << "inputValues data:" << inputValues.data() << "\n";
	// where to allocate the tensors
	auto memoryInfo = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);

	// create the input tensor (this is not a deep copy!)
	/*auto inputOnnxTensor = Ort::Value::CreateTensor<float>(memoryInfo,
		inputValues.data(), inputValues.size(),
		inputShape.data(), inputShape.size());*/
	// Jolin customized
	std::vector<int64_t> input_node_dims = { 1, 4 };
	auto inputOnnxTensor = Ort::Value::CreateTensor<float>(memoryInfo, 
		inputValues.data(), inputValues.size(),
		input_node_dims.data(), 2);

	// the API needs the array of inputs you set and the array of outputs you get
	array inputNames = { inputName };
	array outputNames = { outputName };

	// finally run the inference!
	auto outputValues = session.Run(
		Ort::RunOptions{ nullptr }, // e.g. set a verbosity level only for this run
		inputNames.data(), &inputOnnxTensor, 1, // input to set
		outputNames.data(), 1);					// output to take 

	// extract first (and only) output
	auto& output1 = outputValues[0];
	auto* floats = output1.GetTensorMutableData<float>(); // Get pointer to output tensor float values
	const auto floatsCount = output1.GetTensorTypeAndShapeInfo().GetElementCount();
	getResult(floats, floatsCount);
	// just print the output values
	//std::copy_n(floats, floatsCount, ostream_iterator<float>(cout, " "));
    // pointer array to vector
	vector<double> values(floats, floats + floatsCount);
    std::cout<<"out: "<<values[0]+1 << endl;
	// closing boilerplate
	allocator.Free(inputName);
	allocator.Free(outputName);
}


