
TChain *getCondensetDataByID(int datasetno=3,int n=-1,string directory="/data/chocula/villaa/k100Sim_Data/ZipSum/",string treename="edeptree")
{

   //get data set number string in hex
   string dataset="";
   std::ostringstream oss;
   oss << std::hex << "0x" << std::setfill('0') << std::setw(4) << datasetno;
   dataset = oss.str(); 

  //create a chain
  TChain *data = new TChain(treename.c_str(),treename.c_str());

  //make a command to use with a root pipe
  command = "ls "+directory+" |grep .root |grep "+dataset;
  TString files = gSystem->GetFromPipe(command.c_str());
  istringstream iss(files);

  //get the files from the string
  string filename;

  //make a counter
  int count=0;

  while(!iss.eof()){
    iss >> filename;
    if(n<0 || count<n){
      string fullfilename = directory+"/"+filename;
      data->Add(fullfilename.c_str());
    }
    count++;
  }
  
  return data;

}
