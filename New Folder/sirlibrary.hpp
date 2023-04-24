#ifndef SIRLIBRARY_HPP
#define SIRLIBRARY_HPP

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <typeinfo>

// definizione di una struttura con tre membri: S, I e R
struct SIR {
  double S;
  double I;
  double R;
};
// definizione della classe SIRModel
class SIRModel {
// definisco gli attributi della classe come protected per averne accesso dalla sottoclasse SIRGraph(), che estende la classe SIRModel
//tramite delle librerie ROOT che permettono di creare il grafico dell'andamento del modello SIR in funzionde della durata della simulazione  
    protected: 
        float beta_;
        float gamma_;
        unsigned int days_;
        double N_;
        std::vector<SIR> record_;   // vettore di oggetti di tipo SIR dove andranno salvati i valori
                                    // di S I e R durante l'evoluzione del modello

    public:

  // costruttore della classe che prende i parametri passati da noi da riga di comando 
        SIRModel(SIR sir_zero, float beta, float gamma, unsigned int days);
  

  // funzione che controlla la coerenza dei parametri inseriti da standard input

    void check(); //check su beta e gamma
        
  // funzione di evoluzione del modello
  void dinamic();

  // funzione di stampa con arrotondamenti e vincolo S + I + R = N
  void print();
};

#endif