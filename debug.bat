cls
del bin\NeuralNet.exe
g++ -gdwarf-2 -std=c++11 -Ofast main.cpp NeuralNet.cpp Organism.cpp Simulation.cpp Input.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfgui -o bin\NeuralNet
cd bin
gdb NeuralNet.exe
cd ..