#include "read_audio.h"
#include <string>
#include <math.h>

int main(){

    double input_speech[100000];
    auto [samples, speech] = call("./data/test1.wav");
    std::cout << samples << ',' << speech[0] << std::endl;
    // audio normalize
    // mean
    double mean=0.0, variance=0.0;
    for(int i=0;i<samples;i++){
        mean+=speech[i];
    }
    mean/=samples;
    // variance
    for(int i=0;i<samples;i++){
        variance+=(speech[i]-mean)*speech[i]-mean;
    }
    variance/=samples;
    std::cout<<"mean: "<< mean<<" variance: "<< variance << std::endl;
    for(int i=0;i<100000;i++){
        if(i<samples)
            input_speech[i] = (speech[i]-mean)/std::sqrt(variance+1e-5);
        else
            input_speech[i] = 0;
    }
    std::cout<< input_speech[0] <<"\n";
}