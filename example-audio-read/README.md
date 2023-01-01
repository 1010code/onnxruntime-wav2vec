
## Colab 錄音
[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/1010code/onnxruntime-wav2vec/blob/main/colab_audio_record.ipynb)


## Compile

```
g++ main.cpp read_audio.cpp -o main -std=c++17
./main
```

## WAV File Header

![](./screenshot/img1.png)

![](./screenshot/img2.png)

- ChunkSize (實際檔案大小)
    - 36 + SubChunk2Size, or more precisely:
      4 + (8 + SubChunk1Size) + (8 + SubChunk2Size)
- BitsPerSample
    - 16 bits.
- Subchunk2Size (總samples空間大小bytes)
    - NumSamples * NumChannels * BitsPerSample/8
      This is the number of bytes in the data.
      You can also think of this as the size
      of the read of the subchunk following this number.
    - 因為是 short int(16 bit = 2bytes)，所以單聲道的音訊資料大小為 NumSamples*2 個 bytes

## Reference
- [WAV File Header](https://docs.fileformat.com/audio/wav/)
- [WAV Header Synopsis](https://isip.piconepress.com/projects/speech/software/tutorials/production/fundamentals/v1.0/section_02/s02_01_p05.html)
- [Reading the header of a wav file](https://onestepcode.com/read-wav-header/)
- [WaveFormat]()