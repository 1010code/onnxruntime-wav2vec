#include <onnxruntime_cxx_api.h>
#include <array>
#include <iostream>
#include "read_audio.h"
#include <iomanip>
#include <fstream>

using namespace std;

void getResult(float* floats, int floatsCount) {
    // get vocab array
    std::vector<std::string> inputValues; 
    std::ifstream file("./data/vocab.txt"); 
    while(!file.eof()) 
    {
        std::string i; 
        file >> i; 
        inputValues.emplace_back(i); 
    }
	// pointer array to vector
	std::vector<double> values(floats, floats + floatsCount);
	// range-based for-loop
	for (int i = 0; i < 312; i++) {
        double maxNum = -100;
        int label = 0;
        for(int j=0;j<21128;j++){
            double prob = values[21128*i+j];
            if (prob > maxNum) {
                maxNum = prob;
                label = j;
            }
        }
        if(inputValues[label]!="[PAD]" && inputValues[label]!="|")
            std::cout << inputValues[label];
	}
    printf("\n");
}

int main()
{
    // 模型輸入
    double input_speech[100000];
    // 讀取音檔 16kHz
    auto [samples, speech] = WavfileRead("./data/test5.wav");
    std::cout << "Samples: "<< samples << ",first sample" << speech[0] << std::endl;
    // audio normalize
    normalize(speech, samples, input_speech);
    
	// gives access to the underlying API (you can optionally customize log)
	// you can create one environment per process (each environment manages an internal thread pool)
	Ort::Env env;

	// creates an inference session for a certain model
	Ort::Session session{ env, "./data/ars_wav2vec2_large-xlsr-52-tw.onnx", Ort::SessionOptions{} };

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
	std::vector<float> inputValues;
    inputValues.assign(input_speech, input_speech + 100000);
//     for(int i=0;i<100000;i++){
//         inputValues.push_back(0.01);
//     }
	std::cout << "inputValues size: " << inputValues.size() << "\n";
    std::cout << "input size:" << session.GetInputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape().size()<<" ("<<
        session.GetInputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape()[0]<<", "<<
        session.GetInputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape()[1]<<")\n";
	std::cout << "inputValues data:" << inputValues.data() << "\n";
    std::cout << "output size:" << session.GetOutputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape().size()<<" ("<<
        session.GetOutputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape()[0]<<", "<<
        session.GetOutputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape()[1]<<", "<<
        session.GetOutputTypeInfo(0).GetTensorTypeAndShapeInfo().GetShape()[2]<<")\n";
	// where to allocate the tensors
	auto memoryInfo = Ort::MemoryInfo::CreateCpu(OrtDeviceAllocator, OrtMemTypeCPU);

	// create the input tensor (this is not a deep copy!)
	/*auto inputOnnxTensor = Ort::Value::CreateTensor<float>(memoryInfo,
		inputValues.data(), inputValues.size(),
		inputShape.data(), inputShape.size());*/
	// Jolin customized
	std::vector<int64_t> input_node_dims = { 1, 100000 };
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
	// closing boilerplate
	allocator.Free(inputName);
	allocator.Free(outputName);
}