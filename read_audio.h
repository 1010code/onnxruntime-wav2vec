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
	int sample_rate;
	int byte_rate;
	short int block_align;
	short int bits_per_sample;
	char subchunk2_id[4];
	int subchunk2_size;
} header;

typedef struct header_file *header_p;


void normalize(short int* speech, int samples, double* input_speech);
<<<<<<< HEAD
void normalize_mm(short int* speech, int samples, double* input_speech);
=======
>>>>>>> e972f332ef847d4698177f5faa30f7c1f1bb2f14
std::tuple<int, short int*> WavfileRead(std::string path);