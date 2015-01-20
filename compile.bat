cls
del bin\NeuralNet.exe
g++ -std=c++11 -Ofast main.cpp NeuralNet.cpp -o bin\NeuralNet
cd bin
.\NeuralNet.exe
cd ..