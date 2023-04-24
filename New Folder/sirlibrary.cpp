#include "sirlibrary.hpp"
#include "rootsir.hpp"
//corpo del costruttore
SIRModel::SIRModel(SIR sir_zero, float beta, float gamma, unsigned int days)
            : beta_(beta), gamma_(gamma), days_(days) {
            N_ = sir_zero.S + sir_zero.I + sir_zero.R;
            record_.push_back(sir_zero);}

//corpo della funzione check
void SIRModel::check()  {
        if (typeid(beta_) != typeid(float) || typeid(gamma_) != typeid(float) ||
            beta_ < 0 || beta_ > 1 || gamma_ < 0 || gamma_ > 1) {
            throw std::runtime_error{
              "i parametri beta e gamma devono essere numeri compresi tra zero e "
                "uno"};

        if (typeid(record_[0]) != typeid(SIR) || record_[0].S < 0 || //check su parametri SIR non negativi
            record_[0].I < 0 || record_[0].R < 0) {
            throw std::runtime_error{
                "i parametri S I e R devono essere numeri NON-negativi"};
    }
        if (round(N_) != N_) {
            throw std::runtime_error{"I parametri S I e R devono essere interi"};// check su par SIR 

    }
        if (typeid(days_) != typeid(unsigned int)) {
      throw std::runtime_error{
          "Il numero di giorni di evoluzione del modello deve essere un "
          "intero positivo"};
    }
  } }
// corpo della funzione di dinamica
void SIRModel::dinamic() {
    for (unsigned int j = 0; j < days_; j++) {
      SIR last = record_.back();
      SIR next;
      next.S = last.S - (beta_ * last.S * last.I / N_);
      next.I = last.I + (beta_ * last.S * last.I / N_) - (gamma_ * last.I);
      next.R = last.R + (gamma_ * last.I);
      record_.push_back(next);
    }
    
  }
//corpo della funzione print, vengono eseguiti arrotondamenti in modo da avere il vincolo S + I + R = N per ogni t
void SIRModel::print() {
    std::cout << "      ||####### S ###||### I ###||### R #######||\n";
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








