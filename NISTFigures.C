
#include "RootUtil.C"
#include "histTools.C"
#include "cascadeProd.C"
#include "significance.C"
#include "plotFunctions.C"
#include "plotK100Functions.C"

//best plot commands to use
//plotTSCExample(1,"First",0.7,1e-3,true)
// plotNISTNREDist(1,75,2e-10,1e-12,2.6,true,"PuBeCoinNaI10M");
//  plotSignificance(1,true);

void plotTSCExample(bool print=0,string cascade="First",double ymax=0.7,double ymin=0.0,bool isprelim=true, string ext="eps",bool resave=false)
{

  TLegend *leg;
  leg = new TLegend(0.445,0.82,0.94,0.92);

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
  //c1->SetLogy();
  //c1->SetLogx();
  c1->SetTickx();
  c1->SetTicky();
  c1->SetLeftMargin(xl);
  c1->SetBottomMargin(yb);
  c1->SetTopMargin(yt);
  c1->SetRightMargin(xr);
  //c1->SetGrid(1,1);

  double px=300,py=ymax/2.0;
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
  frame1 = makeFrame(xmin,xmax,ymin,ymax,10,"Calibrated Energy [eV]","Normalized Amplitude [a.u.]",1.2,0.8);
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
  TFile *f1;
  TFile *f10;
  TFile *f100;
  TFile *f1000;
  if(cascade=="First"){
    f1 = new TFile("NISTpreproposal_calculations/cascades_First1.root");
    f10 = new TFile("NISTpreproposal_calculations/cascades_First10.root");
    f100 = new TFile("NISTpreproposal_calculations/cascades_First100.root");
    f1000 = new TFile("NISTpreproposal_calculations/cascades_First1000.root");
  }
  else if(cascade=="Second"){
    f1 = new TFile("NISTpreproposal_calculations/cascades_Second1.root");
    f10 = new TFile("NISTpreproposal_calculations/cascades_Second10.root");
    f100 = new TFile("NISTpreproposal_calculations/cascades_Second100.root");
    f1000 = new TFile("NISTpreproposal_calculations/cascades_Second1000.root");
  }
  else if(cascade=="Third"){
    f1 = new TFile("NISTpreproposal_calculations/cascades_Third1.root");
    f10 = new TFile("NISTpreproposal_calculations/cascades_Third10.root");
    f100 = new TFile("NISTpreproposal_calculations/cascades_Third100.root");
    f1000 = new TFile("NISTpreproposal_calculations/cascades_Third1000.root");
  }

  //get the trees for the data 
  TTree *tf1;
  TTree *tf10;
  TTree *tf100;
  TTree *tf1000;
  if(cascade=="First"){
    tf1 = (TTree*) f1->Get("FirstTSC_whinder1.0");
    tf10 = (TTree*) f10->Get("FirstTSC_whinder10.0");
    tf100 = (TTree*) f100->Get("FirstTSC_whinder100.0");
    tf1000 = (TTree*) f1000->Get("FirstTSC_whinder1000.0");
  }
  else if(cascade=="Second"){
    tf1 = (TTree*) f1->Get("SecondTSC_whinder1.0");
    tf10 = (TTree*) f10->Get("SecondTSC_whinder10.0");
    tf100 = (TTree*) f100->Get("SecondTSC_whinder100.0");
    tf1000 = (TTree*) f1000->Get("SecondTSC_whinder1000.0");
  }
  else if(cascade=="Third"){
    tf1 = (TTree*) f1->Get("ThirdTSC_whinder1.0");
    tf10 = (TTree*) f10->Get("ThirdTSC_whinder10.0");
    tf100 = (TTree*) f100->Get("ThirdTSC_whinder100.0");
    tf1000 = (TTree*) f1000->Get("ThirdTSC_whinder1000.0");
  }

  //create the histograms I want with 60eV nr energy resolution
  double eres=60;
  TH1D *h100;
  TH1D *h1000;
  TH1D *h1000_10PcY;
  if(cascade=="First"){
    h100 = getWithResAndV(tf100,"E1_100",eres);
    h1000 = getWithResAndV(tf1000,"E1_1000",eres);
    h1000_10PcY = getWithResAndV(tf1000,"E1_1000_10PcY",eres,2);
  }
  else if(cascade=="Second"){
    h100 = getWithResAndV(tf1,"M1_1",eres);
    h1000 = getWithResAndV(tf10,"M1_10",eres);
    h1000_10PcY = getWithResAndV(tf10,"M1_10_10PcY",eres,2);
  }
  else if(cascade=="Third"){
    h100 = getWithResAndV(tf10,"M1E2_10",eres);
    h1000 = getWithResAndV(tf100,"M1E2_100",eres);
    h1000_10PcY = getWithResAndV(tf1000,"M1E2_100_10PcY",eres,2);
  }

  //normalize the histograms
  h100->Scale(1/h100->GetBinWidth(1));
  h100->Scale(100.0/(double)tf100->GetEntries());
  h1000->Scale(1/h1000->GetBinWidth(1));
  h1000->Scale(100.0/(double)tf1000->GetEntries());
  h1000_10PcY->Scale(1/h1000_10PcY->GetBinWidth(1));
  h1000_10PcY->Scale(100.0/(double)tf1000->GetEntries());

  //set some colors and line widths
  h100->SetLineColor(kRed);
  h1000->SetLineColor(kBlue);
  h1000_10PcY->SetLineColor(kGreen);
  h100->SetLineWidth(2);
  h1000->SetLineWidth(2);
  h1000_10PcY->SetLineWidth(2);


  leg->AddEntry(h100,Form("Weisskopf hinderance of 100"),"l");
  leg->AddEntry(h1000,Form("Weisskopf hinderance of 1000"),"l");
  leg->AddEntry(h1000_10PcY,Form("Yield increase of 10%%"),"l");

  h100->Draw("same");
  h1000->Draw("same");
  h1000_10PcY->Draw("same");
  //print up legend
  //leg->SetHeader(Form("%d GeV %s primaries ",energy,getFullPartName(part).c_str()));
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetLineWidth(2);
  leg->SetTextFont(42);
  leg->SetTextSize(.03);
  leg->Draw("same");

  //output the file
  if(print){
    plotCanvas(c1,Form("figures/NIST_TSC"),ext);
  }
}
void plotNISTNREDist(bool print=0,int nbins=100,double ymax=1e-6,double ymin=1e-9,double coin=-1.0,bool isprelim=true,string datatype="PuBeCoin_D2O",string path="skim/skimCode/root/", string ext="eps",bool resave=false)
{

  TLegend *leg;


  double primaries=1;
  if(datatype=="PuBeCoin_D2O"){
	  primaries = getPrimaries("0x0028");
	  cout << primaries << endl;
          if(coin<0.0)
            leg = new TLegend(0.50,0.45,0.90,0.65);
          else
            leg = new TLegend(0.51,0.63,0.91,0.754121);
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
            leg = new TLegend(0.389,0.710,0.92,0.8098);
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
  //c1->SetGrid(1,1);

  double px=1104.46,py=1.01e-10;
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
  frame1 = makeFrame(xmin,xmax,ymin,ymax,10,"Total Deposited Energy [eV]","Counts/eV/Neutron",1.2,0.8);
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

  TH1D *hsum = new TH1D("sum","sum",nbins,xmin,xmax);
  hsum->Add(hsing);
  hsum->Add(hmult);
  hsum->SetLineColor(kBlack);
  hsum->SetLineWidth(2);
  cout << hsing << endl;
  cout << hmult << endl;
  cout << hsum << endl;


  //leg->AddEntry(hmult,Form("NR multiples"),"l");
  //leg->AddEntry(hsing,Form("NR singles"),"l");
  leg->AddEntry(hsum,Form("all NR deposits"),"l");

  //get histogram from a quasi-fit to the Poly/NaI data set
  TF1 *f = new TF1("bknd","expo(0)+expo(2)",100,2400);
  f->SetParameter(0,-23.5);
  f->SetParameter(1,-0.007);
  f->SetParameter(2,-25.3);
  f->SetParameter(3,-0.000203555);
  f->SetLineColor(kRed);

  //try making a shaded region
  TGraph *g = new TGraph();
  g->SetPoint(0,xmin,ymin);
  g->SetPoint(1,xmin,f(xmin));
  int npts=100;
  for(int i=0;i<npts;i++){
    double x = xmin+((i+1)*(xmax-xmin)/(double)npts);
    //cout << "x: " << x << " y: " << f(x) << endl;
    g->SetPoint(i+2,x,f(x));
  }
  g->SetPoint(npts+2,xmax,ymin);
  g->SetFillColor(kRed-10);
  g->Draw("f");


  f->Draw("same");

  leg->AddEntry(g,Form("n- and #gamma-induced background NRs"),"f");

  //put a label for cascade features 
  TText *cfeat = new TText(275.893,1e-10,"cascade features");
  cfeat->SetTextAngle(0);
  cfeat->SetTextSize(0.024);
  cfeat->SetTextColor(1);
  cfeat->SetTextFont(42);
  frame1->GetListOfFunctions()->Add(cfeat);

  //arrow to cascade features
  TArrow *a1 = new TArrow(479,9.67e-11,329,6.89e-11,0.01,"|>");
  a1->SetAngle(60);
  a1->SetLineWidth(2);
  TArrow *a2 = new TArrow(479,9.67e-11,425,7.53e-11,0.01,"|>");
  a2->SetAngle(60);
  a2->SetLineWidth(2);
  TArrow *a3 = new TArrow(479,9.67e-11,746.4,8.48e-11,0.01,"|>");
  a3->SetAngle(60);
  a3->SetLineWidth(2);

  a1->Draw();
  a2->Draw();
  a3->Draw();

  //hsing->Draw("same");
  //hmult->Draw("same");
  hsum->Draw("same");
  frame->Draw("sameaxis");
  //print up legend
  //leg->SetHeader(Form("%d GeV %s primaries ",energy,getFullPartName(part).c_str()));
  leg->SetBorderSize(0);
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
    plotCanvas(c1,Form("figures/NIST_NREDist_%s%s",datatype.c_str(),coinlabel.str().c_str()),ext);
  }
}
void plotSignificance(bool print=0,bool isprelim=true, string ext="eps",bool resave=false)
{

  TLegend *leg;
  leg = new TLegend(0.4,0.766,0.92,0.9);

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
    c1 = new TCanvas("c1","Capture Significance",200,10,xw,yw);
  }
  else
    c1 = new TCanvas("c1","Capture Significance",200,10,xw,yw);


  c1->cd();
  //log-log plot
  //c1->SetLogy();
  //c1->SetLogx();
  c1->SetTickx();
  c1->SetTicky();
  c1->SetLeftMargin(xl);
  c1->SetBottomMargin(yb);
  c1->SetTopMargin(yt);
  c1->SetRightMargin(xr);
  //c1->SetGrid(1,1);

  double px=25.736,py=2.2898;
  //size of x-axis
  double xmin=0.0;
  double xmax=60.0;
  double ymin=0.0;
  double ymax=35.0;

  gStyle->SetLineWidth(2);
  gStyle->SetHistLineWidth(1);
  gStyle->SetGridWidth(0);

  //make a frame for this histogram
  TH1* frame1;
  frame1 = makeFrame(xmin,xmax,ymin,ymax,10,"Experiment Duration [d]","Significance [#sigma]",1.2,0.8);
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

  //Use the estimates from N-MISC-16-001, pg 11

  //make the various curves
  //assume duty cycle of 0.5 due to flashing.
  double livefrac=0.86; //300Hz of in-detector rate reading out 500us traces
  double livefrac=0.607; //1kHz of in-detector rate reading out 500us traces
  //if we assume the livefrac is 0.94 and we're reading out 500us traces (pg 13 of N-MISC-16-001)
  cout << "livefrac: " << livefrac << endl;
  //cout << "4xlivefrac: " << fourtimeslivefrac << endl;
  TF1 *f0 = significance(8e-11-1.5e-11,1.5e-11,livefrac,100,false,60,true,0.5); //Poly moderator single NaI coin 40% live
  TF1 *f1 = significance(8e-11-1.5e-11,1.5e-11,livefrac,100,true,60,true,0.5);  //D2O moderator single NaI coin 40% live
  TF1 *f2 = significance(32e-11-6e-11,6e-11,livefrac,100,true,60,true,0.5);   //D2O moderator quad NaI coin 40% live
  TF1 *f3 = significanceLT(4*(1.2e-10+8e-11+7e-11)-4*(9e-12+1.5e-11+2e-11),4*(9e-12+1.5e-11+2e-11),livefrac,100,true,60,true,0.5);   //D2O moderator quad NaI coin 40% live

  //set some colors and line widths
  f0->SetLineColor(kBlack);
  f0->SetLineWidth(2);
  f0->SetNpx(10000);
  f1->SetLineColor(kRed);
  f1->SetLineWidth(2);
  f1->SetNpx(10000);
  f2->SetLineColor(kGreen);
  f2->SetLineWidth(2);
  f2->SetNpx(10000);
  f3->SetLineColor(kBlue);
  f3->SetLineWidth(2);
  f3->SetNpx(10000);

  //calculate days to 8sigma, monotonic functions
  double lbound,ubound,xval,epsilon,siglev;
  siglev=8;
  epsilon=siglev*0.01; //1 % resolution
  lbound=0.0;
  ubound=120.0;
  xval=(ubound+lbound)/2.0;
  while((f0(xval)>(siglev+epsilon)) || (f0(xval)<(siglev-epsilon))){
    if(f0(xval)>(siglev+epsilon)){
      ubound=xval;
      xval=(ubound+lbound)/2.0;
    }
    else{
      lbound=xval;
      xval=(ubound+lbound)/2.0;
    }
  }
  cout << "Function f0 reached " << siglev << "sigma at duration: " << xval << " days" << endl;
  lbound=0.0;
  ubound=120.0;
  xval=(ubound+lbound)/2.0;
  while((f1(xval)>(siglev+epsilon)) || (f1(xval)<(siglev-epsilon))){
    if(f1(xval)>(siglev+epsilon)){
      ubound=xval;
      xval=(ubound+lbound)/2.0;
    }
    else{
      lbound=xval;
      xval=(ubound+lbound)/2.0;
    }
  }
  cout << "Function f1 reached " << siglev << "sigma at duration: " << xval << " days" << endl;
  lbound=0.0;
  ubound=120.0;
  xval=(ubound+lbound)/2.0;
  while((f2(xval)>(siglev+epsilon)) || (f2(xval)<(siglev-epsilon))){
    if(f2(xval)>(siglev+epsilon)){
      ubound=xval;
      xval=(ubound+lbound)/2.0;
    }
    else{
      lbound=xval;
      xval=(ubound+lbound)/2.0;
    }
  }
  cout << "Function f2 reached " << siglev << "sigma at duration: " << xval << " days" << endl;
  lbound=0.0;
  ubound=120.0;
  xval=(ubound+lbound)/2.0;
  while((f3(xval)>(siglev+epsilon)) || (f3(xval)<(siglev-epsilon))){
    if(f3(xval)>(siglev+epsilon)){
      ubound=xval;
      xval=(ubound+lbound)/2.0;
    }
    else{
      lbound=xval;
      xval=(ubound+lbound)/2.0;
    }
  }
  cout << "Function f3 reached " << siglev << "sigma at duration: " << xval << " days" << endl;



  leg->AddEntry(f0,Form("single NaI coincidence > 2.6 MeV"),"l");
  leg->AddEntry(f1,Form("+ D_{2}O moderator"),"l");
  leg->AddEntry(f2,Form("+ 3 NaI detectors"),"l");
  leg->AddEntry(f3,Form("+ decrease threshold to 90 eV"),"l");

  f0->Draw("same");
  f1->Draw("same");
  f2->Draw("same");
  f3->Draw("same");

  //put a label for 8sigma 
  TLatex *sig8 = new TLatex(53.3,8.45,"8#sigma");
  sig8->SetTextAngle(0);
  sig8->SetTextSize(0.024);
  sig8->SetTextColor(1);
  sig8->SetTextFont(42);
  frame1->GetListOfFunctions()->Add(sig8);

  //put a label for precision spectroscopy
  TText *spec = new TText(23.13,20.29,"precision spectroscopy");
  spec->SetTextAngle(0);
  spec->SetTextSize(0.024);
  spec->SetTextColor(1);
  spec->SetTextFont(42);
  frame1->GetListOfFunctions()->Add(spec);

  //make a line with arrow
  TArrow *arr = new TArrow(22,20,22,21,0.007,"|>");
  arr->SetAngle(60);
  arr->SetLineWidth(2);
  arr->Draw();

  //make a line at 20 sigma
  TLine *twentysig = new TLine(0.0,20.0,60.0,20.0);
  twentysig->SetLineWidth(2);
  twentysig->SetLineStyle(2);
  twentysig->Draw("same");

  //make a line at 8 sigma
  TLine *eightsig = new TLine(0.0,8.0,60.0,8.0);
  eightsig->SetLineWidth(2);
  eightsig->SetLineStyle(2);
  eightsig->Draw("same");
  //print up legend
  //leg->SetHeader(Form("%d GeV %s primaries ",energy,getFullPartName(part).c_str()));
  leg->SetBorderSize(0);
  leg->SetFillColor(0);
  leg->SetLineWidth(2);
  leg->SetTextFont(42);
  leg->SetTextSize(.03);
  leg->Draw("same");

  //output the file
  if(print){
    plotCanvas(c1,Form("figures/NIST_Significance"),ext);
  }
}
