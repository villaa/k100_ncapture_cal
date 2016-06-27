/*==================skimData.cpp======================================= 
   
      PROGRAMMER:  Anthony Villano 10/30/12

      UPDATES: 

      06/16/16: A. Villano
                Changed this to accept simulation formats from k100Sim code
       

      PURPOSE: Make a compiled code to skim the data to see if it's faster
               than the root macro in this directory cullEvents.C.
              
======================================================================*/
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <iomanip>


//ROOT stuff
#include "Rtypes.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TEventList.h"
#include "TSystem.h"

using namespace std;

TChain *chainSimData(int &nev,int n=-1,string sim="GenericShield", string source="PuBe", string nprimaries="10M",int datasetno=0,string dir="/data/chocula/villaa/k100Sim_Data/captureCalroot/");
TTree *projectSumDep(TChain *ch,string cut="");
TTree *projectSumDepEv(TChain *ch,string cut="");
int main(int argc, char *argv[])
{
   string rep; 
   string outfile="test.root";
   string outdir="/data/chocula/villaa/k100Sim_Data/ZipSum/";
   string indir="/data/chocula/villaa/k100Sim_Data/captureCalroot/";
   string sim="GenericShield";
   string source="PuBe";
   string nprimaries="10M";
   string dataset="";
   int numfiles=-1;
   int datasetno=0;
   bool evtgrp=false;

   for(int i=0; i<argc; i++)
   {
      rep=argv[i];
      if(rep =="-o")
        outfile = argv[i+1];
      if(rep=="-f")
        numfiles = atoi(argv[i+1]);
      if(rep=="-E")
        evtgrp = true;
      if(rep=="-sim")
        sim = argv[i+1];
      if(rep=="-set")
        datasetno = atoi(argv[i+1]);
      if(rep=="-source")
	source = argv[i+1];
   }

   //get data set number string in hex
   std::ostringstream oss;
   oss << std::hex << "0x" << std::setfill('0') << std::setw(4) << datasetno;
   dataset = oss.str(); 

   //make a command to use with a root pipe
   string command = "ls "+indir+" |grep .root |grep "+sim+" |grep "+dataset+"_ |grep "+source+" |grep "+nprimaries;
   TString files = gSystem->GetFromPipe(command.c_str());
   string files_c = files.Data();
   istringstream iss(files_c);

   //get the files from the string
   string filename;

   //make a counter
   int count=0;

   TChain *data = new TChain("datatree","datatree");
   while(!iss.eof()){
     iss >> filename;
     string fullfilename = indir+filename;
     data->Add(fullfilename.c_str());
     if(numfiles<0 || count%numfiles==0){
       ostringstream convert;
       convert.precision(4);
       convert << setw(4) << setfill('0') << count;
       string outname = outdir+convert.str()+"_"+outfile;
       TFile *newfile = new TFile(outname.c_str(),"RECREATE");
       TTree *tr;
       if(!evtgrp)
         tr = projectSumDep(data,"d3>0.0");
       else
         tr = projectSumDepEv(data,"d3>0.0");
       tr->Write();
       cout << "Writing file: " << outname << endl;
       newfile->Close();
       delete newfile;
       delete data;
       data = new TChain("datatree","datatree");
     }
     //iss >> filename;
     count++;
   }
  
   /*TFile *newfile = new TFile(outfile.c_str(),"RECREATE");
   TTree *tr = projectSumDep(numfiles,"dt==2000 && d3>0.0");

   tr->Write();
   newfile->Close();*/

   cout << "Finished writing file. " << endl;
   return 0;
}
TChain *chainSimData(int &nev,int n,string sim, string source, string nprimaries,int datasetno,string dir)
{
   //get data set number string in hex
   string dataset="";
   std::ostringstream oss;
   oss << std::hex << "0x" << std::setfill('0') << std::setw(4) << datasetno;
   dataset = oss.str(); 

  //create a chain
  TChain *data = new TChain("datatree","datatree");

  //make a command to use with a root pipe
  string command = "ls "+dir+" |grep .root |grep "+sim+"_ |grep "+source+" |grep "+nprimaries+" |grep "+dataset;
  TString files = gSystem->GetFromPipe(command.c_str());
  string files_c = files.Data();
  istringstream iss(files_c);

  //get the files from the string
  string filename;

  //make a counter
  int count=0;

  while(!iss.eof()){
    iss >> filename;
    if(n<0 || count<n){
      string fullfilename = dir+filename;
      data->Add(fullfilename.c_str());
    }
    iss >> filename;
    count++;
  }
  if(n>=0)
    cout << "Chained " << n << " files" << endl;
  else
    cout << "Chained " << count << " files" << endl;

  return data;
}
TTree *projectSumDep(TChain *ch,string cut)
{
  Int_t nev;

  //get tree
  //TChain *ch = chainSimData(nev,n);

  //get a list of unique events consistent with cut
  Long_t htot=0;
  Double_t *tempseed,*seed;
  Double_t *tempev,*ev;

  TEventList allevs("allevs","all events");
  ch->Draw(">>allevs",Form("%s",cut.c_str()),"goff");
  //ch->Draw(">>allevs","dt==2000","goff");
  ch->SetEventList(&allevs);
  ch->Draw("seed:ev","","goff");
  //ch->Draw("seed:ev","dt==2000","goff");
  htot = ch->GetSelectedRows();
  tempseed = ch->GetV1();
  tempev = ch->GetV2();

  //copy over for safety
  cout << htot << endl;
  seed = (Double_t*) malloc(htot*sizeof(Double_t));
  ev = (Double_t*) malloc(htot*sizeof(Double_t));
  for(Long_t i=0; i<htot; i++){
    seed[i] = tempseed[i];
    ev[i] = tempev[i];
  }

  //make new TTree with total edepNR, edepER, nhit, NRhit, ERhit, positions?
  Long64_t nhit,NRhit,ERhit;
  Double_t edepNR,edepER;
   
  // create tree and the ROOT file to store it
  TTree *datatree = new TTree("edeptree","energy deposition data");
   
  // create branches in tree for each data column
  datatree->Branch("nhit",&nhit,"nhit/L");
  datatree->Branch("NRhit",&NRhit,"NRhit/L");
  datatree->Branch("ERhit",&ERhit,"ERhit/L");
  datatree->Branch("edepNR",&edepNR,"edepNR/D");
  datatree->Branch("edepER",&edepER,"edepER/D");

  //loop through the events and make many TEventLists
  //taking care to make sure count unique events only
  Long64_t currseed=0,currev=0,evcount=0;
  //TEventList *evlist;
  for(Long_t i=0; i<htot; i++){
    if(currseed!=(Long64_t)seed[i] || currev!=(Long64_t)ev[i]){
      //cout << Form("seed==%d && ev==%d",(Int_t)seed[i],(Int_t)ev[i]) << endl;
      //found new event
      //evlist = new TEventList("evlist","event list");
      nhit=0;NRhit=0;ERhit=0;
      edepNR=0;edepER=0;
      ch->Draw("type:d3",Form("seed==%d && ev==%d && d3>0.0 && Entry$>=%d",(Int_t)seed[i],(Int_t)ev[i],i),"goff");

      //get the list of useful hits
      Long_t htotsub=0;
      Double_t *typesub;
      Double_t *d3sub;
      htotsub = ch->GetSelectedRows();
      typesub = ch->GetV1();
      d3sub = ch->GetV2();
      for(Int_t j=0;j<htotsub;j++){
        if(((Long64_t)typesub[j] == 11 || (Long64_t)typesub[j] == -11) || (Long64_t)typesub[j] == 22){
          //got ER hit
	  edepER+=d3sub[j];
	  ERhit++;
	  nhit++;
	}
	else if((((Long64_t)typesub[j] -(Long64_t)typesub[j]%10000) > 1) || (Long64_t)typesub[j] == 2112){
          //got NR hit
	  edepNR+=d3sub[j];
	  NRhit++;
	  nhit++;
	}
	else{
	  //what is this?
	}
      }
      datatree->Fill();

      //cout << "Event - " << evcount << endl;
      currseed=(Long64_t)seed[i];
      currev=(Long64_t)ev[i];
      evcount++;
    }
  }


  free(seed);
  free(ev);

  return datatree;
}
TTree *projectSumDepEv(TChain *ch,string cut)
{
  Int_t nev;

  //total number of events
  Long64_t ntot = ch->GetEntries();
  cout << "Processing " << ntot << " events" << endl;
  ch->SetEstimate(ntot);

  //write out the NR and ER cuts as strings
  string ERcut = "(type==11 || type==-11) || type==22";
  string NRcut = "type==2112 || type-type%10000>1";

  //make new TTree with total edepNR, edepER, nhit, NRhit, ERhit, positions?
  Long64_t nhit,NRhit,ERhit;
  Double_t edepNR,edepER;
   
  // create tree and the ROOT file to store it
  TTree *datatree = new TTree("edeptree","energy deposition data");
   
  // create branches in tree for each data column
  datatree->Branch("nhit",&nhit,"nhit/L");
  datatree->Branch("NRhit",&NRhit,"NRhit/L");
  datatree->Branch("ERhit",&ERhit,"ERhit/L");
  datatree->Branch("edepNR",&edepNR,"edepNR/D");
  datatree->Branch("edepER",&edepER,"edepER/D");

  //get meaningful quantities from the tree/chain
  string NRhitstr = "Sum$(1*(("+NRcut+") && ("+cut+")))";
  string ERhitstr = "Sum$(1*(("+ERcut+") && ("+cut+")))";
  string edepNRstr = "Sum$(d3*(("+NRcut+") && ("+cut+")))";
  string edepERstr = "Sum$(d3*(("+ERcut+") && ("+cut+")))";
  ch->Draw(Form("%s:%s:%s:%s",NRhitstr.c_str(),ERhitstr.c_str(),edepNRstr.c_str(),edepERstr.c_str()),"","goff");
  Long64_t nevents = ch->GetSelectedRows();
  Double_t *NRhitvec = ch->GetV1();
  Double_t *ERhitvec = ch->GetV2();
  Double_t *edepNRvec = ch->GetV3();
  Double_t *edepERvec = ch->GetV4();

  //loop through the lists and fill the tree;
  for(Long_t i=0; i<nevents; i++){
    nhit=0;NRhit=0;ERhit=0;
    edepNR=0;edepER=0;

    NRhit=NRhitvec[i];
    ERhit=ERhitvec[i];
    edepNR=edepNRvec[i];
    edepER=edepERvec[i];
    nhit=NRhit+ERhit;
    datatree->Fill();
  }



  return datatree;
}
