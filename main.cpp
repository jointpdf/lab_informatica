//authors: Goffredo Pierbattisti & Giordano Colombo
/*This program is an implementation of the SIR model that recive as input the probability of infection "Beta", the probability of recovery "Gamma", the duration in days of the epidemic and the number of Susceptible, Infected and Recovered at zero time and outputs a complete day-by-day list of the evolution of the numbers of Susceptible, Infected and Recovered and a graphic rapresentation of the three variabiles*/
/*If you want to exclude the part relating to ROOT, simply modify main by initializing a SIRModel object
instead of SIRGraph and canceling the call to the graph() method*/

#include "sir_graph.hpp"    

int main() {
    //Parameters' initialization
    double beta;
    std::cout << "Please enter the probability of infection:\n";
    std::cin >> beta;
    double gamma;
    std::cout << "Please enter the probability of recovery:\n";
    std::cin >> gamma;
    unsigned int days;
    std::cout << "Please enter the duration in days of the epidemic:\n";
    std::cin >> days;
    SIR sir_zero; //memory allocation for an SIR type object
    std::cout << "Please enter the number of Susceptible, Infected ed Recovered at zero time:\n";
    std::cin >> sir_zero.S;
    std::cin >> sir_zero.I;
    std::cin >> sir_zero.R;
    SIRGraph sir (sir_zero, beta, gamma, days);
    //input consistency check, evolution
    sir.check();
    sir.dinamic();
    //graphic rapresentation
    sir.graph();
    //output approximation and print 
    sir.approx();
    sir.print();

    return 0;
}