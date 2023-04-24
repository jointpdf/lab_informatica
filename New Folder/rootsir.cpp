#include "rootsir.hpp"

//implemento le funzioni di SIRGRaph che mi permetteranno di graficare i dati del mio modello SIR

//implemento il costruttore di un oggetto di SIRGraph, il quale ottiene ed inizializza i dati in ingresso sulla falsa riga di SIRModel
SIRGraph::SIRGraph(SIR sir_zero1, float beta1, float gamma1, unsigned int days1) : SIRModel(sir_zero1, beta1, gamma1, days1){}


//funzione che genera il grafico 
void SIRGraph::graphSIR(){
//creo una Canvas vuota con un metodo di root
    TCanvas* canvas = new TCanvas ("sir", "SIR model", 1200, 600);
//scala logaritmica per leggibilità dati quando presenti periodi temporali troppo lunghi
    if (record_.size()>100) 
        {canvas->SetLogx();
        canvas->SetLogy();}
// creo pads in cui inserire gli assi cartesiani e i vari grafici
    TPad* PadS = new TPad("padS", "suscettibili", 0.0, 0.0, 0.33, 1.0);
    TPad* PadI = new TPad("padI", "infetti", 0.33, 0.0, 0.66, 1.0);
    TPad* PadR = new TPad("padR", "rimossi", 0.66, 0.0, 1.0, 1.0);
    PadS->Draw();
    PadI->Draw();
    PadR->Draw();

//Genero il grafico per S in funzione dei giorni della simulazione
    PadS->cd();
    TGraph * graphS = new TGraph();
//Riempio il grafico di S con i dati che provengono dal vettore<SIR> record.S
    for (int i = 0; i<= record_.size(); i++){
        graphS->SetPoint(i, i , record_[i].S);
    }
//Impostazioni grafiche di base tramite medoti di ROOT
    graphS->SetTitle("suscettibili");
    graphS->GetXaxis()->SetTitle("giorni");
    graphS->GetYaxis()->SetTitle("S");
    graphS->SetLineColor(kBlue);
    graphS->Draw("AL");


//Operazioni analoghe a quanto fatto per S, in questo caso per I
    PadI->cd();
    TGraph * graphI = new TGraph();
    for (int j = 0; j<= record_.size(); j++){
        graphI->SetPoint(j, j ,record_[j].I);
    }
    graphI->SetTitle("infetti");
    graphI->GetXaxis()->SetTitle("giorni");
    graphI->GetYaxis()->SetTitle("I");
    graphI->SetLineColor(kRed);
    graphI->Draw("AL");
//Operazioni analoghe a quanto fatto per S, in questo caso per R
    PadR->cd();
    TGraph * graphR = new TGraph();
    for (int k = 0; k<= record_.size(); k++){
        graphR->SetPoint(k, k , record_[k].R);
    }
    graphR->SetTitle("rimossi");
    graphR->GetXaxis()->SetTitle("giorni");
    graphR->GetYaxis()->SetTitle("R");
    graphR->SetLineColor(kGreen);
    graphR->Draw("AL");
//Funzione che salva la Canvas con i tre grafici in un file .png
    canvas->SaveAs("graficoSIR.png");

}