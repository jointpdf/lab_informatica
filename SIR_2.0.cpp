//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include "doctest.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

// definizione di una struttura con tre membri S, I e R
struct SIR {
  double S;
  double I;
  double R;
};

// definizione della classe Epidemic: 4 membri e tre metodi di cui un
// costruttore
class Epidemic {
  std::vector<SIR>
      record_;  // vettore di oggetti di tipo SIR dove andranno salvati i valori
                // di S I e R durante l'evoluzione dell'apidemia
  float beta_;
  float gamma_;
  unsigned int days_;
  double N_;

 public:
  // costruttore
  Epidemic(SIR sir_zero, float beta, float gamma, unsigned int days)
      : beta_(beta), gamma_(gamma), days_(days) {
    N_ = sir_zero.S + sir_zero.I + sir_zero.R;
    record_.push_back(sir_zero);
  }

  // funzione che controlla la coerenza dei parametri inseriti da standard input
  void check() {
    if (typeid(beta_) != typeid(float) || typeid(gamma_) != typeid(float) ||
        beta_ < 0 || beta_ > 1 || gamma_ < 0 || gamma_ > 1) {
      throw std::runtime_error{
          "i parametri beta e gamma devono essere numeri compresi tra zero e "
          "uno"};
    }
    if (typeid(record_[0]) != typeid(SIR) || record_[0].S < 0 ||
        record_[0].I < 0 || record_[0].R < 0) {
      throw std::runtime_error{
          "i parametri S I e R devono essere numeri NON-negativi"};
    }
    if (round(N_) != N_) {
      throw std::runtime_error{"I parametri S I e R devono essere interi"};
    }
    if (typeid(days_) != typeid(unsigned int)) {
      throw std::runtime_error{
          "Il numero di giorni di evoluzione dell'epidemia deve essere un "
          "intero positivo"};
    }
  }

  // funzione di evoluzione dell'epidemia
  void dinamic() {
    for (unsigned int j = 0; j < days_; j++) {
      SIR last = record_.back();
      SIR next;
      next.S = last.S - (beta_ * last.S * last.I / N_);
      next.I = last.I + (beta_ * last.S * last.I / N_) - (gamma_ * last.I);
      next.R = last.R + (gamma_ * last.I);
      record_.push_back(next);
    }
  }

  // funzione di stampa con arrotondamenti e vincolo S + I + R = N
  void print() {
    std::cout << "      ||### S ###||### I ###||### R ###||\n";
    for (std::size_t i = 0; i < record_.size(); i++) {
      if (round(record_[i].S) + round(record_[i].I + round(record_[i].R)) ==
          round(N_)) {
        std::cout << "d_" << i << "        " << round(record_[i].S)
                  << "         " << round(record_[i].I) << "          "
                  << round(record_[i].R) << std::endl;
      }

      else if (round(record_[i].S) + round(record_[i].I + round(record_[i].R)) >
               round(N_)) {
        if (std::min_element(&record_[i].S, &record_[i].R + 1) ==
            &record_[i].S) {
          std::cout << "d_" << i << "        " << round(record_[i].S - 0.5)
                    << "         " << round(record_[i].I) << "          "
                    << round(record_[i].R) << std::endl;
        } else if (std::min_element(&record_[i].S, &record_[i].R + 1) ==
                   &record_[i].I) {
          std::cout << "d_" << i << "        " << round(record_[i].S)
                    << "         " << round(record_[i].I - 0.5) << "          "
                    << round(record_[i].R) << std::endl;
        } else {
          std::cout << "d_" << i << "        " << round(record_[i].S)
                    << "         " << round(record_[i].I) << "          "
                    << round(record_[i].R - 0.5) << std::endl;
        }
      }

      else if (round(record_[i].S) + round(record_[i].I) + round(record_[i].R) <
               round(N_)) {
        if (std::max_element(&record_[i].S, &record_[i].R + 1) ==
            &record_[i].S) {
          std::cout << "d_" << i << "        " << round(record_[i].S + 0.5)
                    << "         " << round(record_[i].I) << "          "
                    << round(record_[i].R) << std::endl;
        } else if (std::max_element(&record_[i].S, &record_[i].R + 1) ==
                   &record_[i].I) {
          std::cout << "d_" << i << "        " << round(record_[i].S)
                    << "         " << round(record_[i].I + 0.5) << "          "
                    << round(record_[i].R) << std::endl;
        } else {
          std::cout << "d_" << i << "        " << round(record_[i].S)
                    << "         " << round(record_[i].I) << "          "
                    << round(record_[i].R + 0.5) << std::endl;
        }

      } else
        std::cout << "la somma non fa N\n";
    }
  }
};

int main() {
  // inizializzazione parametri
  double beta;
  std::cout << "inserisci la probabilita di contagio:\n";
  std::cin >> beta;
  double gamma;
  std::cout << "inserisci la probabilita di guarigione:\n";
  std::cin >> gamma;
  SIR sir_zero;  // costruzione di un oggetto di tipo SIR
  std::cout << "inserisci il numero di Suscettibili, Infetti e Rimossi al "
               "tempo zero:\n";
  std::cin >> sir_zero.S;
  std::cin >> sir_zero.I;
  std::cin >> sir_zero.R;
  int days;
  std::cout << "inserisci la durata in giorni dell'epidemia:\n";
  std::cin >> days;
  if (beta < 0 || beta > 1 || gamma < 0 || gamma > 1) {
    std::cout
        << "ERROR: le probabilita devono essere comprese tra zero e uno\n";
    return 1;
  }
  if (sir_zero.S < 0 || sir_zero.I < 0 || sir_zero.R < 0) {
    std::cout << "ERROR: il numero di suscettibili o infetti o rimossi deve "
                 "essere NON-negativo\n";
    return 1;
  }
  // costruzione di un oggetto di classe Epidemic
  Epidemic epidemia(sir_zero, beta, gamma, days);
  // evoluzione e stampa
  epidemia.dinamic();
  epidemia.check();
  epidemia.print();

  return 0;
}