
#include "RootUtil.C"
#include "histTools.C"
#include "cascadeProd.C"
#include "significance.C"
#include "plotFunctions.C"
#include "plotK100Functions.C"

//best plot commands to use
//  plotSignificance(1,true);

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
