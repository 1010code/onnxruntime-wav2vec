#include "read_audio.h"
#include <fstream>
#include <string>
#include <vector>


int main(){
    // 模型輸入
    double input_speech[100000];
    // 讀取音檔 16kHz
    auto [samples, speech] = WavfileRead("./data/test3.wav");
    std::cout << "Samples: "<< samples << ",first sample" << speech[0] << std::endl;
    // audio normalize
    normalize(speech, samples, input_speech);
    std::cout<< input_speech[0] <<"\n";
    
    std::vector<std::string> inputValues; 
    std::ifstream file("./vocab.txt"); 
    while(!file.eof()) 
    {
        std::string i; 
        file >> i; 
        inputValues.emplace_back(i); 
    }
    std::cout<< inputValues[0] <<"\n";
}