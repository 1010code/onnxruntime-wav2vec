#include "read_audio.h"
#include <string>

int main(){

    auto [data_index, data_buffer] = call("./data/test1.wav");
    std::cout << data_index << ',' << data_buffer[0] << std::endl;
    for(int i=0;i<10;i++){
        std::cout<< data_buffer[i]<<" ";
    }
    std::cout<< std::endl;
}