#ifndef SIRLIB_H
#define SIRLIB_H

#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <typeinfo>

// definizione di una struttura con tre membri S, I e R
struct SIR {
  double S;
  double I;
  double R;
};

class Epidemic {
    private:
  std::vector<SIR> record_;  // vettore di oggetti di tipo SIR dove andranno salvati i valori
                // di S I e R durante l'evoluzione dell'epidemia
  float beta_;
  float gamma_;
  unsigned int days_;
  double N_;
  //vettore dinamica
  //std::vector<SIR> vettore_ritorno;

    public:

  // costruttore
        Epidemic(SIR sir_zero, float beta, float gamma, unsigned int days);
  

  // funzione che controlla la coerenza dei parametri inseriti da standard input

    void check(); //check su beta e gamma
        
  // funzione di evoluzione dell'epidemia
  std::vector<SIR>& dinamic();

  // funzione di stampa con arrotondamenti e vincolo S + I + R = N
  void print();
};







#endif