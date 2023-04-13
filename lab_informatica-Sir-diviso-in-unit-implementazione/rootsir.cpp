#include "rootsir.h"

ù
//setter dei dati 
SIRGraph::SIRGraph(){} //costruttore inizializzato di default
void SIRGraph::setData( std::vector<double>& record_s, std::vector<double>& record_i, std::vector<double>& record_r)
{

    s_record = record_s;

    i_record = record_i;

    r_record = record_r;


}
//funzione che genera il grafico 
void SIRGraph::graphSIR(){

    TCanvas* canvas = new TCanvas ("sir", "SIR model", 1200, 600);
//scala logaritmica per leggibilità dati quando presenti periodi troppo lunghi
    if (s_record.size()>100) 
        {canvas->SetLogx();
        canvas->SetLogy();}
// creo pads in cui inserire gli assi cartesiani

    TPad* PadS = new TPad("padS", "suscettibili", 0.0, 0.0, 0.33, 1.0);
    TPad* PadI = new TPad("padI", "infetti", 0.33, 0.0, 0.66, 1.0);
    TPad* PadR = new TPad("padR", "rimossi", 0.66, 0.0, 1.0, 1.0);
    PadS->Draw();
    PadI->Draw();
    PadR->Draw();

//inizializzo grafico S
    PadS->cd();
    TGraph * graphS = new TGraph();
//for S
    for (int i = 0; i< s_record.size(); i++){
        graphS->SetPoint(i, i , s_record[i]);
    }
    graphS->SetTitle("suscettibili");
    graphS->GetXaxis()->SetTitle("giorni");
    graphS->GetYaxis()->SetTitle("S");
    graphS->SetLineColor(kBlue);
    graphS->Draw("AL");


//for I
    PadI->cd();
    TGraph * graphI = new TGraph();
    for (int j = 0; j< i_record.size(); j++){
        graphI->SetPoint(j, j , i_record[j]);
    }
    graphI->SetTitle("infetti");
    graphI->GetXaxis()->SetTitle("giorni");
    graphI->GetYaxis()->SetTitle("I");
    graphI->SetLineColor(kRed);
    graphI->Draw("AL");
//for R
    PadR->cd();
    TGraph * graphR = new TGraph();
    for (int k = 0; k< r_record.size(); k++){
        graphR->SetPoint(k, k , r_record[k]);
    }
    graphR->SetTitle("rimossi");
    graphR->GetXaxis()->SetTitle("giorni");
    graphR->GetYaxis()->SetTitle("R");
    graphR->SetLineColor(kGreen);
    graphR->Draw("AL");

    canvas->SaveAs("graficoSIR.png");

}