#include <iostream>
#include <stdlib.h>
#include <tuple>
#include <string>

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
	int subchunk2_size; // subchunk2_size denotes the number of samples.
} header;

typedef struct header_file *header_p;



std::tuple<int, short int*> call(std::string path){
    FILE *infile = fopen(path.c_str(), "rb"); // Open wave file in read mode

    short int dataBuffer[4096 * 59];
    int dataIndex = 0;
	int BUFSIZE = 16 * 2; // BUFSIZE can be changed according to the frame size required (eg:512)
	int data_index = 0;
	int count = 0;									  // For counting number of frames in wave file.
	short int buff16[BUFSIZE];						  // short int used for 16 bit as input data format is 16 bit PCM audio
	header_p meta = (header_p)malloc(sizeof(header)); // header_p points to a header struct that contains the wave file metadata fields
	int nb;											  // variable storing number of byes returned
	if (infile)
	{
		fread(meta, 1, sizeof(header), infile);
		std::cout << " Size of Header file is " << sizeof(*meta) << " bytes" << std::endl;
		std::cout << " Sampling rate of the input wave file is " << meta->sample_rate << " Hz" << std::endl;
		std::cout << " Number of samples in wave file are " << meta->subchunk2_size << " samples" << std::endl;

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
		std::cout << " Number of frames in the input wave file are " << count << " "<< data_index << std::endl;
        return {data_index, dataBuffer};
	}

}