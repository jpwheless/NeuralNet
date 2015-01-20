cls
del bin\NeuralNet.exe
g++ -gdwarf-2 -std=c++11 -Ofast main.cpp NeuralNet.cpp -o bin\NeuralNet
cd bin
gdb NeuralNet.exe
cd ..