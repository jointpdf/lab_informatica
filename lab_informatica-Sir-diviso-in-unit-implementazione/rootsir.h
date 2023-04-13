#ifndef ROOTSIR_H
#define ROOTSIR_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <typeinfo>

#include "TCanvas.h"
#include "TGraph.h"
#include "TPad.h"
#include "TSpline.h"
#include "TAxis.h"
#include "TStyle.h"
#include "TImage.h"


class SIRGraph {
//tipo dati necessari per ottenere SIRGraph
private: 
    std::vector<double> s_record;
    std::vector<double> i_record;
    std::vector<double> r_record;
//Costruttore e metodi draw
public:

    SIRGraph(); //costruttore classe
    void setData( std::vector<double>& record_s,std::vector<double>& record_i,std::vector<double>& record_r); //setter dati dinamica
    void graphSIR(); //disegna i grafici per S I R in funzione del tempo in una canvas e la salva come file png

};









#endif