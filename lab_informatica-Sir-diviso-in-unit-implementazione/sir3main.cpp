//main del programma

#include "sirlib.h"
#include "rootsir.h"

int main(){
 // inizializzazione parametri
  double beta;
  std::cout << "inserisci la probabilita di contagio:\n";
  std::cin >> beta;
  double gamma;
  std::cout << "inserisci la probabilita di guarigione:\n";
  std::cin >> gamma;
  ////////////////////////////////////////////////////
  SIR sir_zero;  // costruzione di un oggetto di tipo SIR
    std::cout << "inserisci il numero di Suscettibili al "
               "tempo zero:\n";
    std::cin >> sir_zero.S;
    std::cout << "inserisci il numero di Infetti al "
               "tempo zero:\n";
    std::cin >> sir_zero.I;
    std::cout << "inserisci il numero di Rimossi al "
               "tempo zero:\n";
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
  ////////////////////////////////////
  // costruzione di un oggetto di classe Epidemic
  Epidemic epidemia(sir_zero, beta, gamma, days);
  // evoluzione e stampa
  std::vector<SIR> record_ = epidemia.dinamic();
  //epidemia.dinamic();
  epidemia.check();
  epidemia.print();


/////////////////////////////////////////
// costruzione di un oggetto di classe SIRGraph

SIRGraph graficoSIR;
//std::vector<SIR>& vettore_ritorno = epidemia.dinamic();
//divido il vettore<SIR> in 3 vettori contenenti singolarmente i dati di S I ed R
std::vector<double> vettore_s(record_.size());
std::vector<double> vettore_i(record_.size());
std::vector<double> vettore_r(record_.size());
for(int i = 0; i < record_.size(); i++){
vettore_s[i] = record_[i].S;
vettore_i[i] = record_[i].I;
vettore_r[i] = record_[i].R;};

graficoSIR.setData(vettore_s, vettore_i, vettore_r);

graficoSIR.graphSIR();






    
}