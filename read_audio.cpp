#include <iostream>
#include <stdlib.h>
#include <tuple>
#include <string>
#include <math.h>

typedef struct header_file
{
	char chunk_id[4];
	int chunk_size;
	char format[4];
	char subchunk1_id[4];
	int subchunk1_size;
	short int audio_format;
	short int num_channels;
	int sample_rate; // sample_rate denotes the sampling rate.
	int byte_rate;
	short int block_align;
	short int bits_per_sample;
	char subchunk2_id[4];
	int subchunk2_size;
} header;

typedef struct header_file *header_p;

void normalize(short int* speech, int samples, double* input_speech){
    // mean
    double mean=0.0, variance=0.0;
    for(int i=0;i<samples;i++){
        mean+=speech[i];
    }
    mean/=samples;
    // variance
    for(int i=0;i<samples;i++){
        variance+=(speech[i]-mean)*(speech[i]-mean);
    }
    variance/=samples;
    std::cout<<"mean: "<< mean<<" variance: "<< variance << std::endl;
    for(int i=0;i<100000;i++){
        if(i<samples)
            input_speech[i] = (speech[i]-mean)/std::sqrt(variance+1e-5);
        else
            input_speech[i] = 0;
    }
}
// (signal - MIN) / (MAX-MIN)
void normalize_mm(short int* speech, int samples, double* input_speech){
    // mean
    int min=-32768, max=32767;
    std::cout<<"min: "<< min<<" max: "<< max << std::endl;
    for(int i=0;i<samples;i++){
        double X_std = (speech[i] - min)*1. / (max - min);
        X_std = X_std * (1 - -1) + -1;
        input_speech[i]=X_std;
//         input_speech[i]=speech[i];
//         std::cout<< input_speech[i] << " ";
    }
}

std::tuple<int, short int*> WavfileRead(std::string path){
    FILE *infile = fopen(path.c_str(), "rb"); // Open wave file in read mode

    short int dataBuffer[4096 * 59];
    int dataIndex = 0;
	int BUFSIZE = 16 * 2; // short int 2bytes
	int data_index = 0;
	int count = 0;									  // For counting number of frames in wave file.
	short int buff16[BUFSIZE];						  // short int used for 16 bit as input data format is 16 bit PCM audio
	header_p meta = (header_p)malloc(sizeof(header)); // header_p points to a header struct that contains the wave file metadata fields
	int nb;											  // variable storing number of byes returned
	if (infile)
	{
		fread(meta, 1, sizeof(header), infile);
        std::cout << "-----------------------------------------------------" << std::endl;
		std::cout << " Size of Header: " << sizeof(*meta) << " bytes" << std::endl;
		std::cout << " Sampling rate: " << meta->sample_rate << " Hz" << std::endl;
		std::cout << " File size: " << meta->chunk_size << " bytes"<< std::endl;
        std::cout << " Audio data size: " << meta->subchunk2_size << " bytes"<< std::endl;
            
		while (!feof(infile))
		{
			nb = fread(buff16, 1, BUFSIZE, infile); // Reading data in chunks of BUFSIZE
			// std::cout << nb << std::endl;						// buffer 大小

			/* Insert your processing code here*/
			// 將音訊存入data[] 長度為 4096*59
			if (nb != 0)
			{
                count++; // Incrementing Number of frames
				for (int i = 0; i < 16; i++)
				{
					dataBuffer[data_index++] = buff16[i];
				}
			}
		}
        std::cout << " Number of frames: " << count << std::endl;
		std::cout << " Number of samples: " << data_index << std::endl;
        std::cout << "-----------------------------------------------------" << std::endl;
        return {data_index, dataBuffer};
	}

}