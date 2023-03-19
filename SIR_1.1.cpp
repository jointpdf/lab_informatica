//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
//#include "doctest.h"
#include <iostream>
#include <vector>

//definizione di una struttura con tre membri S, I e R
struct SIR {
    double S;
    double I;
    double R;
};

//definizione della classe Epidemic: 4 membri e tre metodi di cui un costruttore
class Epidemic {
    std::vector<SIR> record_;   //vettore di oggetti di tipo SIR dove andranno salvati i valori di S I e R durante l'evoluzione dell'apidemia
    double beta_;
    double gamma_;
    int days_;
 
 public:
    //costruttore
    Epidemic (SIR sir_zero, double beta, double gamma, int days):
        beta_(beta), 
        gamma_(gamma), 
        days_(days) {
        record_.push_back(sir_zero);  
    }
    //funzione di evoluzione dell'epidemia
    void dinamic (){
        for (int j=0; j<days_; j++){
            SIR last = record_.back();
            SIR next;
            const double N = record_[0].S + record_[0].I + record_[0].R;
            next.S = last.S - (beta_ * last.S * last.I / N);
            next.I = last.I + (beta_ * last.S * last.I / N) - (gamma_ * last.I);
            next.R = last.R + (gamma_ * last.I);
            record_.push_back(next);
        }
    }
    //funzione di stampa
    void print (){
        std::cout <<"      ||### S ###||### I ###||### R ###||\n";
        for (std::size_t i=0; i < record_.size(); i++){
            
            std::cout <<"d_"<< i
                      <<"        "<< static_cast<int>(record_[i].S)
                      <<"         "<< static_cast<int>(record_[i].I)
                      <<"          "<< static_cast<int>(record_[i].R) <<std::endl;
        }
    }
};


int main (){
    //inizializzazione parametri
    double beta;
    std::cout << "inserisci la probabilita di contagio:\n";
    std::cin >> beta;
    double gamma;
    std::cout << "inserisci la probabilita di guarigione:\n";
    std::cin >> gamma;
    SIR sir_zero;  //costruzione di un oggetto di tipo SIR
    std::cout <<"inserisci il numero di Suscettibili, Infetti e Rimossi al tempo zero:\n";
    std::cin >> sir_zero.S;
    std::cin >> sir_zero.I;
    std::cin >> sir_zero.R;
    int days;
    std::cout <<"inserisci la durata in giorni dell'epidemia:\n";
    std::cin >> days;
    if (beta<0 || beta>1 || gamma<0 || gamma>1){
        std::cout <<"ERROR: le probabilita devono essere comprese tra zero e uno\n";
        return 1;
    }
    if (sir_zero.S<0 || sir_zero.I<0 || sir_zero.R<0){
        std::cout <<"ERROR: il numero di suscettibili o infetti o rimossi deve essere NON-negativo\n";
        return 1;
    }
    //costruzione di un oggetto di classe Epidemic
    Epidemic epidemia (sir_zero, beta, gamma, days);
    //evoluzione e stampa
    epidemia.dinamic();
    epidemia.print();
    
    return 0;
}

/*il problema principale da risolvere risulta quello legato all'approssimazione delle variabili "S" "I" e "R" da double a int
  che non rispetta il vincolo N = S + I + R*/