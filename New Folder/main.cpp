//autori: Goffredo Pierbattisti & Giordano Colombo
//main del programma che genera un modello SIR, stampando a schermo S I R e il numero di giorni di simulazione corrispondenti
//e genera tramite librerie ROOT il grafico di S, I ed R in funzione del tempo.
//Qualora si voglia escludere la parte inerente a ROOT è sufficiente modificare il main inizializzando un oggetto di SIRModel
//invece che di SIRGraph e cancellando la chiamata alla funzione .graphSIR()
#include "sirlibrary.hpp" //librerie del modello, sirlibrary.hpp viene inserita qui nel main in maniera ricorsiva per poter separare 
                          //la parte di root, qualora necessario necessario
#include "rootsir.hpp"    

int main(){
 // inizializzazione parametri gamma e beta del modello SIR
  double beta, gamma;
  std::cout << "inserisci la probabilita di infezione:\n";
  std::cin >> beta;
  std::cout << "inserisci la probabilita di rimozione:\n";
  std::cin >> gamma;
//////////
  SIR sir_zero;  // costruzione di un oggetto di tipo SIR in cui mettere i valori iniziali di SIR
    std::cout << "inserisci il numero di Suscettibili al "
               "tempo zero:\n";
    std::cin >> sir_zero.S;
    std::cout << "inserisci il numero di Infetti al "
               "tempo zero:\n";
    std::cin >> sir_zero.I;
    std::cout << "inserisci il numero di Rimossi al "
               "tempo zero:\n";
  std::cin >> sir_zero.R;
// inizializzazione durata modello in giorni
  int days;
  std::cout << "inserisci la durata in giorni dell'modelloSIR:\n";
  std::cin >> days;
// gestione valori iniziali errati 
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
//creazione di un oggetto di tipo SIRGraph, su cui applicheremo i metodi della classe SIRGraph
//qualora si voglia separare dalla parte di root, sostituire SIRGRAPH con SIRModel
 SIRGraph modelloSIR(sir_zero, beta, gamma, days);
//dinamica modello, check sui parametri e stampa a schermo dei valori 
  
  modelloSIR.check();
  modelloSIR.dinamic();
  modelloSIR.print();
////////////////////////////////////////
//generazione del grafico contenente i valori del vettore<SIR> con librerie ROOT, qualora 
//sia necessario disattivare la parte inerente a ROOT, commentare la riga seguente 
modelloSIR.graphSIR();

return 0;    
}