[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/1010code/onnxruntime-wav2vec/blob/main/colab_audio_record.ipynb)

## Install ONNXRuntime
此範例在樹莓派上運行 ONNXRuntime。從官方下載動態連接庫後並安裝到系統目錄下。

```
sudo cp ./onnxruntime-linux-x64-1.12.1/lib/libonnxruntime.so.1.12.1 /usr/local/lib/
sudo ldconfig
```

## Compile

```
g++ wav2vec.cpp read_audio.cpp -o main -I onnxruntime-linux-x64-1.12.1/include -Lonnxruntime-linux-x64-1.12.1/lib -lonnxruntime -std=c++17

g++ main.cpp read_audio.cpp -o main -std=c++17
```