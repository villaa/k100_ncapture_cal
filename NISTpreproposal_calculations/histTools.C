
TH1D *getWithResAndV(TTree *t,string name="TSC",double res=10,double V=0)
{
  //add a resolution in eV to a spectrum of V volts
  TRandom3 *rand = new TRandom3();

  //make histogram
  TH1D *h = new TH1D(name.c_str(),name.c_str(),100,50,600);

  double E,I;

  t->SetBranchAddress("E",&E);
  t->SetBranchAddress("I",&I);

  for(int i=0;i<t->GetEntries();i++){
    t->GetEntry(i);
    h->Fill(rand->Gaus(E+V*I,res));
  }

  return h;
}
