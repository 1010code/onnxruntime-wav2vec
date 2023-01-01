#include "read_audio.h"

int main(){
    // 模型輸入
    double input_speech[100000];
    // 讀取音檔 16kHz
    auto [samples, speech] = WavfileRead("../data/test3.wav");
    std::cout << "Samples: "<< samples << std::endl;
    // audio normalize
    normalize(speech, samples, input_speech);
    std::cout<< input_speech[0] <<"\n";
}

