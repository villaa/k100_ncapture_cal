
#include "RootUtil.C"
#include "plotFunctions.C"
#include "plotK100Functions.C"

void plotNREDist(bool print=0,int nbins=100,double ymax=1e-6,double ymin=1e-9,double coin=-1.0,bool isprelim=true,string datatype="PuBeCoin_D2O",string path="skim/skimCode/root/", string ext="eps",bool resave=false)
{

  TLegend *leg;


  double primaries=1;
  if(datatype=="PuBeCoin_D2O"){
	  primaries = getPrimaries("0x0028");
	  cout << primaries << endl;
          if(coin<0.0)
            leg = new TLegend(0.50,0.45,0.90,0.65);
          else
            leg = new TLegend(0.520376,0.553571,0.920063,0.754121);
            //leg = new TLegend(0.50,0.27,0.90,0.47);
  }
  else if(datatype=="PuBeCoin10M"){
	  primaries = getPrimaries("0x001b");
          if(coin<0.0)
            leg = new TLegend(0.50,0.68,0.90,0.88);
          else
            leg = new TLegend(0.50,0.407,0.90,0.608);
  }
  else if(datatype=="PuBeCoinNaI10M"){
	  primaries = getPrimaries("0x0000");
          if(coin<0.0)
            leg = new TLegend(0.50,0.68,0.90,0.88);
          else
            leg = new TLegend(0.50,0.407,0.90,0.608);
  }
  primaries=primaries*1e7;
  cout << primaries << endl;
  
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
    c1 = new TCanvas("c1","Nuclear Recoil Energy Scale",200,10,xw,yw);
  }
  else
    c1 = new TCanvas("c1","Nuclear Recoil Energy Scale",200,10,xw,yw);


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
  c1->SetGrid(1,1);

  double px=1581,py=ymax/2.0;
  //size of x-axis
  double xmin=100.0;
  double xmax=2400;
  //double ymin=1.0e-1;
  //double ymax=1e4;

  gStyle->SetLineWidth(2);
  gStyle->SetHistLineWidth(1);
  gStyle->SetGridWidth(0);

  //make a frame for this histogram
  TH1* frame1;
  frame1 = makeFrame(xmin,xmax,ymin,ymax,10,"Total Deposited Energy [eV]","counts/eV/neutron",1.2,0.8);
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

  cout << (double)primaries << endl;
  //make a chain and histograms
  TChain *ch = getCondensetDataByPrefix(datatype,-1,path);
  TH1D *hsing = getDetNREDistK100(ch,nbins,xmin,xmax,"singles",coin);
  hsing->SetLineColor(kRed);
  hsing->Scale(1/((double)primaries*hsing->GetBinWidth(1)));
  hsing->SetLineWidth(2);
  TH1D *hmult = getDetNREDistK100(ch,nbins,xmin,xmax,"mult",coin);
  hmult->SetLineColor(kBlue);
  hmult->Scale(1/((double)primaries*hmult->GetBinWidth(1)));
  hmult->SetLineWidth(2);
  TH1D *her = getDetNREDistK100(ch,nbins,xmin,xmax,"er",coin);
  her->SetLineColor(kGreen);
  her->Scale(1/((double)primaries*her->GetBinWidth(1)));
  her->SetLineWidth(2);
  TH1D *hermix = getDetNREDistK100(ch,nbins,xmin,xmax,"ermix",coin);
  hermix->SetLineColor(kMagenta);
  hermix->Scale(1/((double)primaries*hermix->GetBinWidth(1)));
  hermix->SetLineWidth(2);

  TH1D *hsum = new TH1D("sum","sum",nbins,xmin,xmax);
  hsum->Add(hsing);
  hsum->Add(hmult);
  hsum->Add(her);
  hsum->Add(hermix);
  hsum->SetLineColor(kBlack);
  hsum->SetLineWidth(2);
  cout << hsing << endl;
  cout << hmult << endl;
  cout << her << endl;
  cout << hermix << endl;
  cout << hsum << endl;


  leg->AddEntry(hmult,Form("NR multiples"),"l");
  leg->AddEntry(hsing,Form("NR singles"),"l");
  leg->AddEntry(her,Form("ER events"),"l");
  leg->AddEntry(hermix,Form("ER/NR events"),"l");
  leg->AddEntry(hsum,Form("all NR deposits"),"l");

  hsing->Draw("same");
  hmult->Draw("same");
  her->Draw("same");
  hmult->Draw("same");
  hsum->Draw("same");
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
    plotCanvas(c1,Form("figures/NREDist_%s%s",datatype.c_str(),coinlabel.str().c_str()),ext);
  }
}
