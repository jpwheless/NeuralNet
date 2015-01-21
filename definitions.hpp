// Global definitions

#ifndef DEFINITIONS_HPP
#define DEFINITIONS_HPP

#define PI 3.14159265359
#define PI2 6.28318530718
#define constrain(amt,low,high) ((amt)<(low)?(low):((amt)>(high)?(high):(amt)))

#define RESX 1000.0
#define RESY 1000.0

#define TICK_TIME 0.0166666666666667

#define NN_INPUTS 7
#define NN_OUTPUTS 2
#define NN_SHAPE {NN_INPUTS,7,5,NN_OUTPUTS}

#endif