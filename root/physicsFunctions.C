#include <algorithm>

TH1D *readPuBeSpectrum_Cont(string file="pube_continuous.txt",string out="pube.dat")
{
  //the input file is understood to be input from data theif and
  //is roughly continous with the format:
  //#header
  //x0, y0
  //x1, y1 ...
  
  ifstream infile(file.c_str(),ios::in);
  string line;

  getline(infile,line);

  //store in vectors
  vector<double> xvec,yvec;

  char numbers[100];
  while(!getline(infile,line).eof()){
    istringstream data(line);
    data.getline(numbers, 100, ',');
    xvec.push_back(atof(numbers)); 
    data.getline(numbers, 100, ',');
    yvec.push_back(atof(numbers)); 
  }

  //I'm sorting this here because for whatever
  //reason it's out of order in the data theif file 
  
  Double_t *sort_xvec;
  sort_xvec = malloc((xvec.size())*sizeof(Double_t));
  for(int i=0;i<xvec.size();i++) sort_xvec[i] = xvec[i]; 
  Double_t *sort_yvec;
  sort_yvec = malloc((xvec.size())*sizeof(Double_t));
  for(int i=0;i<xvec.size();i++) sort_yvec[i] = yvec[i]; 
  Int_t *index;
  index = malloc((xvec.size())*sizeof(Int_t));
  TMath::Sort(xvec.size(),sort_xvec,index,kFALSE);
  for(int i=0;i<xvec.size();i++) xvec[i] = sort_xvec[index[i]]; 
  for(int i=0;i<xvec.size();i++) yvec[i] = sort_yvec[index[i]]; 


  if(xvec.size()==0) return NULL;

  double del;
  if(xvec.size()>1)
    del = xvec[1]-xvec[0];
  else
    del = -xvec[0];

  cout << std::setprecision(10);
  Double_t *xbins;
  xbins = malloc((xvec.size()+1)*sizeof(Double_t));
  xbins[0] = xvec[0] - del;
  for(int i=0;i<xvec.size();i++) xbins[i+1] = xvec[i]; 
  TH1D *h =  new TH1D("pube","pube",xvec.size(),xbins);

  for(int i=0;i<xvec.size();i++) h->SetBinContent(i+1,yvec[i]);

  ofstream outfile("pube.dat");

  outfile << std::setprecision(10);
  for(int i=0;i<xvec.size();i++){
    if(h->GetBinLowEdge(i+1)>0.0){
	    outfile << h->GetBinLowEdge(i+1)+h->GetBinWidth(i+1)/2.0 << "  " << h->GetBinContent(i+1)/h->Integral() << endl; 
    }
  }

  return h;
}
