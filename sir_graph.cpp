#include "sir_graph.hpp"

//Constructor: inherits its behavior from the superclass
SIRGraph::SIRGraph(SIR sir_zero, float beta, float gamma, unsigned int days) : SIRModel(sir_zero, beta, gamma, days){}

//Method that allows you to graphically display the trend of the three variables S, I and R over time
void SIRGraph::graph(){
    //For each of the variables S, I and R is allocated a different TGraph object
    //TGraph is an object made of two arrays x and y with npoints each
    TGraph * graphS = new TGraph();
    graphS->SetTitle("Susceptible");
    graphS->GetXaxis()->SetTitle("Days");
    graphS->GetYaxis()->SetTitle("Number");
    graphS->SetLineColor(kBlue);

    TGraph * graphI = new TGraph();
    graphI->SetTitle("Infected");
    graphI->GetXaxis()->SetTitle("Days");
    graphI->GetYaxis()->SetTitle("Number");
    graphI->SetLineColor(kRed);

    TGraph * graphR = new TGraph();
    graphR->SetTitle("Removed");
    graphR->GetXaxis()->SetTitle("Days");
    graphR->GetYaxis()->SetTitle("Number");
    graphR->SetLineColor(kGreen);

    //TGraphs are used to save the information contained in the record_ vector by filling them with points of the type (x, y) = (i, record_[i].A)
    //Method of TGraph class that allow you to add points: void AddPoint (double x, double y)
    for (std::size_t i = 0; i < record_.size(); i++){
        graphS-> AddPoint (static_cast<double> (i) , record_[i].S);
        graphI-> AddPoint (static_cast<double> (i) , record_[i].I);
        graphR-> AddPoint (static_cast<double> (i) , record_[i].R);
    }
    
    //Allocation of a TCanvas object
    //A TCanvas is an area mapped to a window directly under the control of the display manager.
    TCanvas* canvas = new TCanvas ("sir", "SIR model", 1200, 600);
    
    //The Canvas is split into three Pads
    TPad* padS = new TPad("padS", "suscettibili", 0.0, 0.0, 0.33, 1.0);
    TPad* padI = new TPad("padI", "infetti", 0.33, 0.0, 0.66, 1.0);
    TPad* padR = new TPad("padR", "rimossi", 0.66, 0.0, 1.0, 1.0);
    padS -> Draw ();
    padI -> Draw ();
    padR -> Draw ();

    //In each Pad one of the three variables S, I and R is drawn
    padS -> cd ();
    graphS -> Draw("AL");
    
    padI -> cd ();
    graphI -> Draw("AL");

    padR -> cd ();
    graphR -> Draw("AL");
    
    canvas->SaveAs("graficoSIR.png");

    //Memory deallocation
    delete graphS;
    delete graphI;
    delete graphR;
    delete canvas;
}