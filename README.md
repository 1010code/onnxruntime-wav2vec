[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/1010code/onnxruntime-wav2vec/blob/main/colab_audio_record.ipynb)

## Install ONNXRuntime
此範例在 linux-x64 上運行 ONNXRuntime。從官方下載動態連接庫後並安裝到系統目錄下。

```
sudo cp ./onnxruntime-linux-x64-1.12.1/lib/libonnxruntime.so.1.12.1 /usr/local/lib/
sudo ldconfig
```

## Compile

```
# Intel CPU
g++ wav2vec.cpp read_audio.cpp -o main -I onnxruntime-linux-x64-1.12.1/include -Lonnxruntime-linux-x64-1.12.1/lib -lonnxruntime -std=c++17
g++ silero_en.cpp read_audio.cpp -o main -I onnxruntime-linux-x64-1.12.1/include -Lonnxruntime-linux-x64-1.12.1/lib -lonnxruntime -std=c++17

./main
```

```
# Arm CPU
g++ wav2vec.cpp read_audio.cpp -o main -I onnxruntime-linux-aarch64-1.12.1/include -Lonnxruntime-linux-aarch64-1.12.1/lib -lonnxruntime -std=c++17
g++ silero_en.cpp read_audio.cpp -o main -I onnxruntime-linux-aarch64-1.12.1/include -Lonnxruntime-linux-aarch64-1.12.1/lib -lonnxruntime -std=c++17

./main
```


- test1 (goodmorning this is a beautiful day)
- test2 (hello what's your name)
- test3 (an apple a day keeps the doctor away)
- test4 (what time is it)


## Reference

```
wget 
```