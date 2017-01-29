//calculate the significance of the measurement given some known parameters as a function of time (in days)

TF1 *significance(double sig,double bknd,double livetime,double sigwidth,bool d20boost=false, double dres0=10,double srcrate=1e6)
{

  //sig is signal in events/ev/neutron
  //bknd is background in same unit
  //livetime is the livetime fraction
  //sigwidth is the width (in eV) of the assumed gaussian signal

  //double sigfac = 0.68; //assume 1sigma is exactly 50eV
  double sigfac = 0.3; 
  double factor; 
  if(d20boost)
    factor = (sig*20*srcrate*24*60*60*livetime*sigfac*2.4)/sqrt(bknd*100*srcrate*24*60*60*livetime*3.0);
  else
    factor = (sig*20*srcrate*24*60*60*livetime*sigfac)/sqrt(bknd*100*srcrate*24*60*60*livetime);
  TF1 *f = new TF1("significance",Form("%f*x/sqrt(x)",factor),0,60);

  return f;
}
