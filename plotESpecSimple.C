#include "plotCaptureFunctions.C"


void plotESpecSimple(int datasetno=3){
TH1D *h = getDetEDist(300,0.0,2.5,true,0,NULL,datasetno,"/data/chocula/villaa/k100Sim_Data/ZipSum/");
TH1D *her = getDetEDist(300,0.0,2.5,true,1,NULL,datasetno,"/data/chocula/villaa/k100Sim_Data/ZipSum/");
her->SetLineColor(kGreen);
TH1D *hms = getDetEDist(300,0.0,2.5,false,0,NULL,datasetno,"/data/chocula/villaa/k100Sim_Data/ZipSum/");
TH1D *hmix = getDetEDist(300,0.0,2.5,true,2,NULL,datasetno,"/data/chocula/villaa/k100Sim_Data/ZipSum/");
hmix->SetLineColor(kMagenta);
h->SetLineColor(kRed);
h->Draw();
hms->Draw("same");
her->Draw("same");
hmix->Draw("same");

//get the sum
TH1D *hsum = getDetEDist(300,0.0,2.5,true,0,NULL,datasetno,"/data/chocula/villaa/k100Sim_Data/ZipSum/");
hsum->SetLineColor(kBlack);
hsum->SetLineWidth(2);
hsum->Add(her);
hsum->Add(hms);
hsum->Add(hmix);
hsum->Draw("same");
c1->SetLogy();


}
