#include <iostream>
#include <fstream>
#include <sstream>

#include "TVector3.h"
#include "TFile.h"
#include "TNtuple.h"

Int_t makecartesianmap( std::string filename = "TPC_fld_map_f_shiftby2p85cm.table" )
{
  std::ifstream ifs( filename ); 
  std::string line; 

  double x,y,z;
  double bx,by,bz;
  double gauss2tesla = 1.0/10000.0;
  
  std::string rootfile = "sphenix3dmapxyz.root";
  TFile *f = new TFile(rootfile.c_str(),"recreate");
  TNtuple fieldmap("fieldmap","sPHENIX 3D Field Map TPC_fld_map_f_shiftby2p85cm.table 2020.01.16 (Tesla)","x:y:z:bx:by:bz");
  
  int linenum = 0; 
  while (getline (ifs, line)) { 
    //    std::cout << line << std::endl;
    std::istringstream iss(line); 
    iss >> x >> y >> z >> bx >> by >> bz;
    if ( iss.rdstate() & std::ios::failbit ) {
      std::cout << "ignore line: " << line << std::endl;
      continue;
    }
    std::cout << x << "," << y << "," << z << "," << bx << "," << by << "," << bz << std::endl;
    
    fieldmap.Fill(x,y,z,bx*gauss2tesla,by*gauss2tesla,bz*gauss2tesla);

    linenum++; 
  }
  
  f->Write();

  return linenum;
}
