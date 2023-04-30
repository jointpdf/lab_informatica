#ifndef SIRMODEL_HPP
#define SIRMODEL_HPP

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <typeinfo>

// Definition of a structure with three public member: S, I and R
struct SIR {
  double S;
  double I;
  double R;
};

// SIRModel class definition 
class SIRModel {
    protected: // class attributes are defined as protectet to ensure their accessibility to a subclasse "SIRGrafph" (defined in "sir_graph" library) 
        float beta_;
        float gamma_;
        unsigned int days_;
        double N_;
        std::vector<SIR> record_;   //vector where the values of S I and R will be saved during the model evolution

    public:
        // Constructor
        SIRModel(SIR sir_zero, float beta, float gamma, unsigned int days);
        // Method that performs a consistency check on the types of the STDIN inserted parameters
        void check();
        // Method which calculates day by day the evolution of the values of S, I and R and saves them in the member vector "record_"
        void dinamic();
        // Rounding method that guarantee the constrain S + I + R = N
        void approx();
        // Standard output print method
        void print();
};

#endif
