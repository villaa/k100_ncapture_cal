#include "weisskopf.C"
#include "lindhard.C"
#include "kinematics.C"
#include <time.h>

//make a file with datasets for whinder of 1,10,100.
void collectData(int n, double whinder=1,string TSC="First",string filename="out.root")
{
  TFile *f = new TFile(filename.c_str(),"UPDATE");
  ULong64_t seed = clock();
  cout << "Clock seed: " << seed << endl;
  TRandom3 *rand = new TRandom3(seed);
  if(TSC=="First")
    TTree *t = gatherFirstTSC(n,rand,whinder);
  else if(TSC=="Second")
    TTree *t = gatherSecondTSC(n,rand,whinder);
  else if(TSC=="Third")
    TTree *t = gatherThirdTSC(n,rand,whinder);

  t->Write("",TObject::kOverwrite);

  return;
}

//make a data set with some examples of a two step cascade
//two-step cascade (TSC) in the 72Ge(n,gamma)73Ge reaction where the
//capture goes from 6783(Sn)-->392 keV (3/2-) --> 66.7 (metastable) keV (5/2+).  This can be E1 or M2
//and the Weisskopf estimate for it is ~9fs. 
//geDecay(geStop(300.64,getMass("73Ge")/1000,9,rand),getMass("73Ge")/1000,0.392,rand)
TTree *gatherThirdTSC(int n,TRandom3 *rand,double whinder=1,string filename="out.root")
{
  //take the TSC commented above and create a root tree with just the energy for n events

  //the input whinder is the hinderance factor wrt Weisskopf estimates, for E1 this seems
  //to be as much as 10^4
  double E; //total energy of cascade in eV
  double I; //ionization in number of e/h pairs
  UInt_t seed=rand->GetSeed();
  TTree *t = new TTree(Form("ThirdTSC_whinder%3.1f",whinder),Form("ThirdTSC_whinder%3.1f",whinder));
  t->Branch("E",&E,"E/D");
  t->Branch("seed",&seed,"seed/i");
  t->Branch("I",&I,"I/D"); //ionization in effective number of e/h pairs assuming egam=3eV (average energy to make one e/h pair);

  //construct a lindhard parameter set 
  Double_t par[1];
  par[0]=0.159; //k-value for Germanium (accepted)
  Double_t x[1];
  Double_t y[1];

  //do the loop
  for(int i=0;i<n;i++){
    E=300.64;
    I=0;
    double vdecay = geStop(E,getMass("73Ge")/1000,we(1.132,73,"M1")*whinder,rand);
    double Eleft = ((getMass("73Ge")*1e6)/2.0)*(pow(vdecay,2.0));
    x[0]=300.64;
    y[0]=Eleft;
    //cout << "Lindhard x: " << lindhard_k(x,par) << endl;
    //cout << "Lindhard y: " << lindhard_k(y,par) << endl;
    I+=(x[0]*lindhard_k(x,par)/3.0)-(y[0]*lindhard_k(y,par)/3.0);
    E+=-Eleft;
    double Erest = geDecay(vdecay,getMass("73Ge")/1000.0,1.132,rand);
    E+=Erest;
    x[0]=Erest;
    //cout << "Lindhard x: " << lindhard_k(x,par) << endl;
    I+=(x[0]*lindhard_k(x,par)/3.0);
    //cout << "Ionization I: " << I << endl;
    t->Fill();
  }

  return t;
}
//make a data set with some examples of a two step cascade
//two-step cascade (TSC) in the 72Ge(n,gamma)73Ge reaction where the
//capture goes from 6783(Sn)-->1132 keV (1/2-) --> 0 keV (1/2-).  This can be M1
//and the Weisskopf estimate for it is ~fs. 
//geDecay(geStop(218.71,73,1,rand),73,1.1320,rand)
TTree *gatherSecondTSC(int n,TRandom3 *rand,double whinder=1,string filename="out.root")
{
  //take the TSC commented above and create a root tree with just the energy for n events

  //the input whinder is the hinderance factor wrt Weisskopf estimates, for E1 this seems
  //to be as much as 10^4
  double E; //total energy of cascade in eV
  double I; //ionization in number of e/h pairs
  UInt_t seed=rand->GetSeed();
  TTree *t = new TTree(Form("SecondTSC_whinder%3.1f",whinder),Form("SecondTSC_whinder%3.1f",whinder));
  t->Branch("E",&E,"E/D");
  t->Branch("seed",&seed,"seed/i");
  t->Branch("I",&I,"I/D"); //ionization in effective number of e/h pairs assuming egam=3eV (average energy to make one e/h pair);

  //construct a lindhard parameter set 
  Double_t par[1];
  par[0]=0.159; //k-value for Germanium (accepted)
  Double_t x[1];
  Double_t y[1];

  //do the loop
  for(int i=0;i<n;i++){
    E=218.71;
    I=0;
    double vdecay = geStop(E,getMass("73Ge")/1000,we(1.132,73,"M1")*whinder,rand);
    double Eleft = ((getMass("73Ge")*1e6)/2.0)*(pow(vdecay,2.0));
    x[0]=218.71;
    y[0]=Eleft;
    //cout << "Lindhard x: " << lindhard_k(x,par) << endl;
    //cout << "Lindhard y: " << lindhard_k(y,par) << endl;
    I+=(x[0]*lindhard_k(x,par)/3.0)-(y[0]*lindhard_k(y,par)/3.0);
    E+=-Eleft;
    double Erest = geDecay(vdecay,getMass("73Ge")/1000.0,1.132,rand);
    E+=Erest;
    x[0]=Erest;
    //cout << "Lindhard x: " << lindhard_k(x,par) << endl;
    I+=(x[0]*lindhard_k(x,par)/3.0);
    //cout << "Ionization I: " << I << endl;
    t->Fill();
  }

  return t;
}
//make a data set with some examples of a two step cascade
//two-step cascade (TSC) in the 70Ge(n,gamma)71Ge reaction where the
//capture goes from 7416(Sn)-->2032 keV (1/2-,3/2) --> 0 keV (1/2-).  This can be E1
//and the Weisskopf estimate for it is a hundred times less than ~fs. 
//geDecay(geStop(204.61,71,10000000,rand),71,2.032,rand)
TTree *gatherFirstTSC(int n,TRandom3 *rand,double whinder=1,string filename="out.root")
{
  //take the TSC commented above and create a root tree with just the energy for n events

  //the input whinder is the hinderance factor wrt Weisskopf estimates, for E1 this seems
  //to be as much as 10^4
  double E; //total energy of cascade in eV
  double I; //ionization in number of e/h pairs
  UInt_t seed=rand->GetSeed();
  TTree *t = new TTree(Form("FirstTSC_whinder%3.1f",whinder),Form("FirstTSC_whinder%3.1f",whinder));
  t->Branch("E",&E,"E/D");
  t->Branch("seed",&seed,"seed/i");
  t->Branch("I",&I,"I/D"); //ionization in effective number of e/h pairs assuming egam=3eV (average energy to make one e/h pair);

  //construct a lindhard parameter set 
  Double_t par[1];
  par[0]=0.159; //k-value for Germanium (accepted)
  Double_t x[1];
  Double_t y[1];

  //do the loop
  for(int i=0;i<n;i++){
    E=204.61;
    I=0;
    double vdecay = geStop(E,getMass("71Ge")/1000,we(2.032,71,"E1")*whinder,rand);
    double Eleft = ((getMass("71Ge")*1e6)/2.0)*(pow(vdecay,2.0));
    x[0]=204.61;
    y[0]=Eleft;
    //cout << "Lindhard x: " << lindhard_k(x,par) << endl;
    //cout << "Lindhard y: " << lindhard_k(y,par) << endl;
    I+=(x[0]*lindhard_k(x,par)/3.0)-(y[0]*lindhard_k(y,par)/3.0);
    E+=-Eleft;
    double Erest = geDecay(vdecay,getMass("71Ge")/1000.0,2.032,rand);
    E+=Erest;
    x[0]=Erest;
    //cout << "Lindhard x: " << lindhard_k(x,par) << endl;
    I+=(x[0]*lindhard_k(x,par)/3.0);
    //cout << "Ionization I: " << I << endl;
    t->Fill();
  }

  return t;
}
//return the Energy after the mid-stop kick. 
double geDecay(double v, double M, double Egam, TRandom3 *rand)
{

  //assume v in units of c, M in GeV, and Egam in MeV.

  //generate a random direction wrt the incoming direction in the CM
  //I think one angle will do, the azimuthal angle shouldn't matter
  double costhet = (2*rand->Uniform())-1;
  double sinthet = sqrt(1-pow(costhet,2.0));

  //calculate the recoiling energy in the CM frame
  double Ecm = pow(Egam*1e6,2.0)/(2*(M*1e9));

  //cout << "Ecm: " << Ecm << endl;

  //boost to the lab frame using the velocity v in the direction -z
  double vx,vy;
  double vxpr,vypr;
  double vxnew,vynew;
  vx = sqrt(2*M*1e9*Ecm)/(M*1e9);
  vy = 0.0;
  vxpr = costhet*vx -sinthet*vy;
  vypr = sinthet*vx + costhet*vy;
  vxnew = vxpr + v;
  vynew = vypr;

  //cout << "vx: " << vx << endl;
  //cout << "vy: " << vy << endl;
  //cout << "vxpr: " << vxpr << endl;
  //cout << "vypr: " << vypr << endl;
  //cout << "vxnew: " << vxnew << endl;
  //cout << "vynew: " << vynew << endl;

  //now calculate the energy
  double El;
  El = ((M*1e9)/2.0)*(pow(vxnew,2.0)+pow(vynew,2.0));

  //return the energy in eV 
  return El;
}
//return the velocity at a random stopping time
double geStop(double E, double M, double tau, TRandom3 *rand)
{
  //assume energy in eV, mass in GeV, tau in fs.
  
  //get the random time, time and tau in fs
  double t = rand->Exp(tau);

  //return the instantaneous velocity
  return vgeS2(E,M,t);
}
//constant stopping power stopping. return distance after time t for initial energy E and mass M
double rgeS2(double E, double M, double t)
{
  //assume energy in eV, mass in GeV, t in fs.
  //return velocity in units of c
  //NS2 = s2 * (E/eps) * (rho/R)
  
  //constants
  //need hbar as eV*fs so I can put a time into 1/eV like t/hbar
  double hbar = 0.6582119; //converted with google
  double hbarc = 197.327; //eV*nm

  //stopping power (constant)
  //double s2 = 0.32; //from Lindhard Paper Notes on Atomic Collisions II
  //if you're going to use a constant 0.1 is probably a better estimate in this region
  double s2 = 0.1; //from Lindhard Paper Notes on Atomic Collisions II

  //number density in natural units
  double Ntilde = 3.3739e-10; //in MeV**3
  Ntilde*=1e18;


  //calculate z-factor
  double z1=32.0;
  double z2=32.0;
  double zfac = (z1*z2)/(sqrt(pow(z1,(2/3.0))+pow(z2,(2/3.0))));

  //cout << "zfac: " << zfac << endl;

  //NS2 (see notes N-misc-17-001 pg 6) in eV**2
  //I think I dropped a 4pi in that calculation though, restored here
  double NS2 = 4*TMath::Pi()*s2*Ntilde*0.8853*zfac*((M*1e9/511e3)/(2*M*1e9)); //in eV**2

  //calculate maximum range and time
  double Rmax = (1/(4.0*TMath::Pi()))*(1/Ntilde)*(1/(s2*0.8853*zfac))*E*((2*M*1e9)/(M*1e9/511e3));
  double tmax = Rmax * sqrt(2*M*1e9/E);

  //cout << "Rmax: " << Rmax*hbarc << endl;
  //cout << "tmax: " << tmax*hbar << endl;
  //cout << "Pi: " << TMath::Pi() << endl;

  double R = (2*(M*1e9)*E - pow((sqrt(2*(M*1e9)*E) - NS2*t/hbar),2.0))/(2*(M*1e9)*NS2); 

  if(t>tmax*hbar)
    return Rmax*hbarc;
  else
    return R*hbarc;
}
//constant stopping power stopping. return velocity after time t for initial energy E and mass M
double vgeS2(double E, double M, double t)
{

  //constants
  //need hbar as eV*fs so I can put a time into 1/eV like t/hbar
  double hbar = 0.6582119; //converted with google
  double hbarc = 197.327; //eV*nm

  double R = rgeS2(E,M,t);
  R/=hbarc;

  //stopping power (constant)
  //double s2 = 0.32; //from Lindhard Paper Notes on Atomic Collisions II
  //if you're going to use a constant 0.1 is probably a better estimate in this region
  double s2 = 0.1; //from Lindhard Paper Notes on Atomic Collisions II

  //number density in natural units
  double Ntilde = 3.3739e-10; //in MeV**3
  Ntilde*=1e18;


  //calculate z-factor
  double z1=32.0;
  double z2=32.0;
  double zfac = (z1*z2)/(sqrt(pow(z1,(2/3.0))+pow(z2,(2/3.0))));

  //cout << "zfac: " << zfac << endl;

  //NS2 (see notes N-misc-17-001 pg 6) in eV**2
  //I think I dropped a 4pi in that calculation though, restored here
  double NS2 = 4*TMath::Pi()*s2*Ntilde*0.8853*zfac*((M*1e9/511e3)/(2*M*1e9)); //in eV**2

  //calculate maximum range and time
  double Rmax = (1/(4.0*TMath::Pi()))*(1/Ntilde)*(1/(s2*0.8853*zfac))*E*((2*M*1e9)/(M*1e9/511e3));
  double tmax = Rmax * sqrt(2*M*1e9/E);

  if(t>tmax*hbar)
    return 0.0;
  else
    return sqrt(2*M*1e9*(E-NS2*R))/(M*1e9);
}
Double_t vgeS2func(Double_t *x,Double_t *par)
{
  //parameters are starting energy in eV and mass in GeV
  Double_t E = par[0];
  Double_t M = par[1];

  //the independent variable x is time in fs

  return vgeS2(E,M,x[0]);

}
