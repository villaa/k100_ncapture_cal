
#include "RootUtil.C"
#include "histTools.C"
#include "cascadeProd.C"
#include "significance.C"

void plotTSCExample(bool print=0,int nbins=100,double ymax=1e-6,double ymin=1e-9,bool isprelim=true, string ext="eps",bool resave=false)
{

  TLegend *leg;


  //let's do some calculations to make the axis size ratio correct for some specified
  //ratio of x-size to y-size.  
  int xw=810,yw=200;
  double r=1.0;
  double xr = 0.05;
  double xl = 0.15;
  double yt = 0.05;
  double yb = 0.12;
  double padsp=0.1;

  findCanvasSize(xw,yw,1,1,r,xr,xl,yt,yb,padsp);

  gROOT->SetStyle("Plain");
  //make a canvas
  TCanvas* c1 = (TCanvas*) gROOT->GetListOfCanvases()->FindObject("c1");
  if(c1){
    c1->Close();
    c1 = new TCanvas("c1","Capture TSC",200,10,xw,yw);
  }
  else
    c1 = new TCanvas("c1","Capture TSC",200,10,xw,yw);


  c1->cd();
  //log-log plot
  c1->SetLogy();
  //c1->SetLogx();
  c1->SetTickx();
  c1->SetTicky();
  c1->SetLeftMargin(xl);
  c1->SetBottomMargin(yb);
  c1->SetTopMargin(yt);
  c1->SetRightMargin(xr);
  //c1->SetGrid(1,1);

  double px=1581,py=ymax/2.0;
  //size of x-axis
  double xmin=50.0;
  double xmax=600.0;
  //double ymin=1.0e-1;
  //double ymax=1e4;

  gStyle->SetLineWidth(2);
  gStyle->SetHistLineWidth(1);
  gStyle->SetGridWidth(0);

  //make a frame for this histogram
  TH1* frame1;
  frame1 = makeFrame(xmin,xmax,ymin,ymax,10,"Calibrated Energy [eV]","normalized amplitude",1.2,0.8);
  if(isprelim){
    TText *prelim = new TText(px,py,"preliminary");
    prelim->SetTextAngle(0);
    prelim->SetTextSize(0.1);
    prelim->SetTextColor(17);
    prelim->SetTextFont(42);
    frame1->GetListOfFunctions()->Add(prelim);
  }
  frame1->Draw();
  //TAxis *xaxis = frame1->GetXaxis();
  //xaxis->SetNoExponent(true);

  //make some new gstyles for thick lines
  //https://root.cern.ch/root/html/TStyle.html#TStyle:SetLineStyleString
  gStyle->SetLineStyleString(12,"36 36"); //dashed
  gStyle->SetLineStyleString(13,"12 24"); //dotted
  gStyle->SetLineStyleString(14,"36 48 12 48"); //dash-dot
  gStyle->SetLineStyleString(15,"60 36 12 36 12 36 12 36"); //dash-triple-dot

  //I guess use the first cascade --generalize later

  //open the files for hinderance factors of 1,100,1000
  TFile *f1 = new TFile("NISTpreproposal_calculations/cascades_First1.root");
  TFile *f100 = new TFile("NISTpreproposal_calculations/cascades_First100.root");
  TFile *f1000 = new TFile("NISTpreproposal_calculations/cascades_First1000.root");

  //get the trees for the data 
  TTree *tf1 = f1->Get("FirstTSC_whinder1.0");
  TTree *tf100 = f100->Get("FirstTSC_whinder100.0");
  TTree *tf1000 = f1000->Get("FirstTSC_whinder1000.0");

  //create the histograms I want
  TH1D *h100 = getWithResAndV(tf100,"E1_100",60);
  TH1D *h1000 = getWithResAndV(tf1000,"E1_1000",60);
  TH1D *h1000_10PcY = getWithResAndV(tf1000,"E1_1000_10PcY",60,2);

  //set some colors and line widths
  h100->SetLineColor(kRed);
  h1000->SetLineColor(kBlue);
  h1000_10PcY->SetLineColor(kGreen);
  h100->SetLineWidth(2);
  h1000->SetLineWidth(2);
  h1000_10PcY->SetLineWidth(2);


  leg->AddEntry(h100,Form("Weisskopf hinderance 100"),"l");
  leg->AddEntry(h1000,Form("Weisskopf hinderance 100"),"l");
  leg->AddEntry(h1000_10PcY,Form("Yield increase 10\%"),"l");

  h100->Draw("same");
  h1000->Draw("same");
  h1000_10PcY->Draw("same");
  //print up legend
  //leg->SetHeader(Form("%d GeV %s primaries ",energy,getFullPartName(part).c_str()));
  leg->SetFillColor(0);
  leg->SetLineWidth(2);
  leg->SetTextFont(42);
  leg->SetTextSize(.03);
  leg->Draw("same");

  ostringstream coinlabel;
  if(coin>0.0)
    coinlabel << "_coin" << ((int)(coin*10))/10;

  //output the file
  if(print){
    plotCanvas(c1,Form("figures/TSC",datatype.c_str(),coinlabel.str().c_str()),ext);
  }
}
