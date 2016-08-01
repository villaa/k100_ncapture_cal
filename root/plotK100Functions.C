#include "physicalFunctions.C"
#include "chainDataFunctions.C"

TH1D *getDetNREDistK100(TChain *ch,int bins=100,double xmin=0.0, double xmax=5.0,string type="singles",double coin=-1.0,bool resave=false)
{

  //create a histogram
  TH1D *h = new TH1D("edep","edep",bins,xmin,xmax);

  ostringstream cut;
  cut << "(edepNR+edepER)>"<<xmin<<" && (edepNR+edepER)<"<<xmax;

  if(coin>0.0)
    cut <<" && edepCoin>"<<coin<<" && tdiffCoin<10000";
  //fill the histogram
  if(type=="singles"){
    cut << " && NRhit==1 && ERhit==0";
    ch->Draw("edepNR+edepER>>edep",Form("%s",cut.str().c_str()),"goff");
  }
  else if(type=="mult"){
    cut << " && NRhit>1 && ERhit==0";
    ch->Draw("edepNR+edepER>>edep",Form("%s",cut.str().c_str()),"goff");
  }
  else if(type=="mult"){
    cut << " && NRhit>1 && ERhit==0";
    ch->Draw("edepNR+edepER>>edep",Form("%s",cut.str().c_str()),"goff");
  }
  else if(type=="er"){
    cut << " && NRhit==0 && ERhit>0";
    ch->Draw("edepNR+edepER>>edep",Form("%s",cut.str().c_str()),"goff");
  }
  else if(type=="ermix"){
    cut << " && NRhit>0 && ERhit>0";
    ch->Draw("edepNR+edepER>>edep",Form("%s",cut.str().c_str()),"goff");
  }
  else{
    ch->Draw("edepNR+edepER>>edep",Form("%s",cut.str().c_str()),"goff");
  }

  return h;
}
