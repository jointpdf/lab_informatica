#ifndef SIRGRAPH_HPP
#define SIRGRAPH_HPP

//RootCern libraries
#include "TCanvas.h"
#include "TGraph.h"
#include "TPad.h"
#include "TAxis.h"

//The sir_model library is included to have inheritance
#include "sir_model.hpp"

//SIRGraph class definition as a derived class form SIRModell
class SIRGraph : public SIRModel {
    public:
        SIRGraph(SIR sir_zero, float beta, float gamma, unsigned int days);
        void graph(); //method that draws the graphs for S I R as a function of time in a canvas and saves it as a png file in 3 Pads of a single Canvas
};

#endif
