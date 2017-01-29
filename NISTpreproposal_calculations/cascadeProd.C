//return the velocity at a random stopping time
double geStop(double E, double M, double tau, TRandom3 *rand)
{
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
