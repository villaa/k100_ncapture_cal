//calculate the significance of the measurement given some known parameters as a function of time (in days)

TF1 *significance(double sig,double bknd,double livetime,double sigwidth,bool d20boost=false, double dres0=10,bool realdays=false,double dutycycle=0.5,double srcrate=1e6)
{

  //sig is signal in events/ev/neutron
  //bknd is background in same unit
  //livetime is the livetime fraction
  //sigwidth is the width (in eV) of the assumed gaussian signal

  //account for resolution and timing broadening
  double sigtotal = sqrt(pow(dres0,2.0)+pow(200,2.0)); //broadened by 200 at least

  //double sigfac = 0.68; //assume 1sigma is exactly 50eV
  double sigfac = TMath::Erf((50.0/sigtotal)*(1/sqrt(2))); //assume 100 eV analysis region
  cout << "sigfac: " << sigfac << endl;

  //note the estimates below were based on a histogram with a certain bin width, they might seem contrived but the numbers are recorded
  //in the notebook N-MISC-16-001 pg 11. 
  double factor; 
  if(d20boost)
    factor = (sig*20*srcrate*24*60*60*livetime*sigfac*2.4)/sqrt(bknd*100*srcrate*24*60*60*livetime*3.0);
  else
    factor = (sig*20*srcrate*24*60*60*livetime*sigfac)/sqrt(bknd*100*srcrate*24*60*60*livetime);
  TF1 *f;
 
  if(realdays)
    f = new TF1("significance",Form("%f*(x/sqrt(x))*(%f/sqrt(%f))",factor,dutycycle,dutycycle),0,60);
  else
    f = new TF1("significance",Form("%f*x/sqrt(x)",factor),0,60);

  return f;
}
TF1 *significanceLT(double sig,double bknd,double livetime,double sigwidth,bool d20boost=false, double dres0=10,bool realdays=false,double dutycycle=0.5,double srcrate=1e6)
{

  //sig is signal in events/ev/neutron
  //bknd is background in same unit
  //livetime is the livetime fraction
  //sigwidth is the width (in eV) of the assumed gaussian signal

  //account for resolution and timing broadening
  double sigtotal = sqrt(pow(dres0,2.0)+pow(200,2.0)); //broadened by 200 at least

  //double sigfac = 0.68; //assume 1sigma is exactly 300eV
  double sigfac = TMath::Erf((150.0/sigtotal)*(1/sqrt(2))); //assume 300 eV analysis region
  cout << "sigfac: " << sigfac << endl;

  //note the estimates below were based on a histogram with a certain bin width, they might seem contrived but the numbers are recorded
  //in the notebook N-MISC-16-001 pg 11. 
  double factor; 
  if(d20boost)
    factor = (sig*20*srcrate*24*60*60*livetime*sigfac*2.4)/sqrt(bknd*300*srcrate*24*60*60*livetime*3.0);
  else
    factor = (sig*20*srcrate*24*60*60*livetime*sigfac)/sqrt(bknd*300*srcrate*24*60*60*livetime);
  TF1 *f;
 
  if(realdays)
    f = new TF1("significance",Form("%f*(x/sqrt(x))*(%f/sqrt(%f))",factor,dutycycle,dutycycle),0,120);
  else
    f = new TF1("significance",Form("%f*x/sqrt(x)",factor),0,120);

  return f;
}
TF1 *significanceNSF(double sig,double bknd,double livetime,double sigwidth, double dres0=200,bool realdays=false,double dutycycle=0.5)
{
  //all assuming 90V for now
  //all assuming 200 eV resolution on peaks

  //sig is signal in events/10days
  //bknd is background in same unit -- expect, say 100 events over the whole range 0 to 25 keV
  bknd*=(1200.0/25000.0); //so we can quote the background over the whole interval
  //livetime is the livetime fraction
  //sigwidth is the width (in eV) of the assumed gaussian signal

  //account for resolution and timing broadening
  double sigtotal = sqrt(pow(dres0,2.0));

  //double sigfac = 0.68; //assume 1sigma is exactly 50eV
  double sigfac = TMath::Erf((600/sigtotal)*(1/sqrt(2))); //assume 1200 eV analysis region
  cout << "sigfac: " << sigfac << endl;

  double factor; 
  factor = ((sig/10.0)*livetime*sigfac)/sqrt((bknd/10.0)*livetime); //src and bknds are in units of 10 days
  TF1 *f;
 
  if(realdays)
    f = new TF1("significance",Form("%f*(x/sqrt(x))*(%f/sqrt(%f))",factor,dutycycle,dutycycle),0,60);
  else
    f = new TF1("significance",Form("%f*x/sqrt(x)",factor),0,60);

  return f;
}
