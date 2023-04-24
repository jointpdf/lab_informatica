#ifndef ROOTSIR_HPP
#define ROOTSIR_HPP

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <typeinfo>
// includo varie librerie ROOT 
#include "TCanvas.h"
#include "TGraph.h"
#include "TPad.h"
#include "TSpline.h"
#include "TAxis.h"
#include "TStyle.h"
#include "TImage.h"

#include "sirlibrary.hpp" // includo sirlib per avere ereditarietà
// Sto costruendo una classe SIRGraph che estende, utilizzando funzionalità root, la classe di partenza SIRModel;
// Uso l'ereditarietà per far avere accesso a SIRGraph agli attributi protetti della classe SIRModel e ai suoi metodi pubblici
class SIRGraph : public SIRModel {


//Costruttore e metodi draw per
public:

    SIRGraph(SIR sir_zero1, float beta1, float gamma1, unsigned int days1); //costruttore oggetto della classe SIRGraph sulla falsa riga della classe SIRModel
            
    void graphSIR(); //disegna i grafici per S I R in funzione del tempo in una canvas e la salva come file png in 3 pad divisi su un'unica finestra

};







#endif