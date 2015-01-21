cls
del bin\NeuralNet.exe
g++ -std=c++11 -Ofast main.cpp NeuralNet.cpp Organism.cpp Simulation.cpp Input.cpp Environment.cpp Food.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfgui -o bin\NeuralNet
cd bin
.\NeuralNet.exe
cd ..