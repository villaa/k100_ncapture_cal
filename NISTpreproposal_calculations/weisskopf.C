
//estimate the lifetime of a state in fs, given mutipolarity from:
//Eq. 5 Nucl. Data A 2, 347 (1966)
double we(double Egam,double A,string transition="E1")
{
  //Egam is in MeV, A is integer mass number, transition is [E1,M1,E2,M2 ... etc]
  //only calculated in that paper up to L=3. 
  double width=-1; //width in eV

  //constants
  //need hbar as eV*fs so I can put a time into 1/eV like t/hbar
  double hbar = 0.6582119; //converted with google

  if(transition=="E1"){
    width = 6.748e-2*pow(A,(2.0/3.0))*pow(Egam,3);
  }
  else if(transition=="M1"){
    width = 2.072e-2*pow(Egam,3);
  }
  else if(transition=="E2"){
    width = 4.792e-8*pow(A,(4.0/3.0))*pow(Egam,5);
  }
  else if(transition=="M2"){
    width = 1.472e-8*pow(A,(2.0/3.0))*pow(Egam,5);
  }
  else if(transition=="E3"){
    width = 2.233e-14*pow(A,(2.0))*pow(Egam,7);
  }
  else if(transition=="M3"){
    width = 6.856e-15*pow(A,(4.0/3.0))*pow(Egam,7);
  }
  else{
    cout << "ERROR! we:: unrecognized multipole, output negative" << endl; 
  }

  return hbar/width;
}
