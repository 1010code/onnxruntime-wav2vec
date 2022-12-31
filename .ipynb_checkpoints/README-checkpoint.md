
```
sudo cp ./onnxruntime-linux-x64-1.12.1/lib/libonnxruntime.so.1.12.1 /usr/local/lib/
sudo ldconfig
```

g++ iris_DNN.cpp -o main -I onnxruntime-linux-x64-1.12.1/include -Lonnxruntime-linux-x64-1.12.1/lib -lonnxruntime -std=c++17
g++ wav2vec.cpp read_audio.cpp -o main -I onnxruntime-linux-x64-1.12.1/include -Lonnxruntime-linux-x64-1.12.1/lib -lonnxruntime -std=c++17

g++ main.cpp read_audio.cpp -o main -std=c++17