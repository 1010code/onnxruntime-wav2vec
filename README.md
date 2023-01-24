[![Open In Colab](https://colab.research.google.com/assets/colab-badge.svg)](https://colab.research.google.com/github/1010code/onnxruntime-wav2vec/blob/main/example-audio-read/colab_audio_record.ipynb)

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

### 中文測試資料
- test1 今天天氣很好出太陽了
- test2 我早上起床後就去運動
- test3 麥克風測試我今天早上起床吃了一個蛋餅
- test4 下午我去百貨公司買了一雙鞋子跟一個皮包
- test5 我今天早上去運動非常的開心


### 英文測試資料
- test1 (goodmorning this is a beautiful day)
- test2 (hello what's your name)
- test3 (an apple a day keeps the doctor away)

## Download pre-train model
pre-trained STT models.

```
wget https://models.silero.ai/models/en/en_v5.onnx -P data
wget https://models.silero.ai/models/en/en_v1_labels.json -p data
gdown "https://drive.google.com/uc?export=download&confirm=no_antivirus&id=1sKUGYv6IDchKDApmtLbWmj3Zbwk_uJ_U"
```

## Reference

- [silero-models config file](https://raw.githubusercontent.com/snakers4/silero-models/master/models.yml)
