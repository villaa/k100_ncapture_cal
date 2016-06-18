#include "physicalFunctions.C"
#include "chainDataFunctions.C"

TH1D *getDetEDist(int bins=100,double xmin=0.0, double xmax=5.0,bool singles=false, int nrermix=0, TChain *datatree = NULL,int datasetno=3, string directory="/data/chocula/villaa/k100Sim_Data/ZipSum/")
{
  //NOTE nrermix has decoding:
  //0: NRs
  //1: ERs
  //2: mix

  //get the tree
  if(datatree==NULL){
    datatree = getCondensetDataByID(3,-1,directory,"edeptree");
  }


  //open the file and get the tree
  //cout << "Opening file: " << file << endl;
  //TFile *f = new TFile(file.c_str());
  //if(!f){
  //  cout << "getDetEDist_Delayed: ERROR! could not read file" << endl;
  //  return NULL;
  //}
  //TTree *datatree = f->Get("edeptree");
  //cout << "Tree is: " << datatree << endl;
  //datatree->Print();

  //create a histogram
  TH1D *h = new TH1D("edep","edep",bins,xmin,xmax);
  cout << "Histogram is: " << h << endl;




  //fill
  if(nrermix==0 && singles )
    datatree->Draw("edepNR*1000>>edep","NRhit==1 && ERhit==0","goff");

  if(nrermix==0 && !singles )
    datatree->Draw("edepNR*1000>>edep","NRhit>1 && ERhit==0","goff");

  if(nrermix==1)
    datatree->Draw("edepER*1000>>edep","NRhit==0 && ERhit>0","goff");

  if(nrermix==2)
    datatree->Draw("edepNR*1000+edepER*1000>>edep","NRhit>0 && ERhit>0","goff");

  return h;
}
