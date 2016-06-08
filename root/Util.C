
string roundTime(double time)
{
  string output;

  //make some vars
  vector<string> suffix;
  vector<double> magnitude;
  suffix.push_back("s");
  magnitude.push_back(1);
  suffix.push_back("ms");
  magnitude.push_back(1e3);
  suffix.push_back("mus");
  magnitude.push_back(1e6);
  suffix.push_back("ns");
  magnitude.push_back(1e9);
  suffix.push_back("ps");
  magnitude.push_back(1e12);
  suffix.push_back("fs");
  magnitude.push_back(1e15);
  //find out how much we have to multiply by to make it > 1
  for(int i; i<magnitude.size();i++){

    if(magnitude[i]*time>=1){
      output = Form("%04d_%s",(int)(magnitude[i]*time),suffix[i].c_str());
      break;
    }
  }

  return output;
}
