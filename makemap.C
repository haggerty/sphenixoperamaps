#include <iostream>
#include <fstream>
#include <sstream>

#include "TVector3.h"
#include "TFile.h"
#include "TNtuple.h"

Int_t makemap( std::string filename = "TPC_fld_map_f.table" )
{
  std::ifstream ifs( filename ); 
  std::string line; 

  double x,y,z;
  double bx,by,bz;
  
  double r,phi;
  double br,bphi;

  std::string rootfile = "sphenix3dmap_0.root";
  TFile *f = new TFile(rootfile.c_str(),"recreate");
  TNtuple B("B","sPHENIX 3D Field Map 2020.01.14 (Gauss)","r:phi:z:br:bphi:bz");
  TVector3 position;
  TVector3 bfield;
  
  int linenum = 0; 
  while (getline (ifs, line)) { 
    //    std::cout << line << std::endl;
    std::istringstream iss(line); 
    iss >> x >> y >> z >> bx >> by >> bz;
    if ( iss.rdstate() & std::ios::failbit ) {
      std::cout << "ignore line: " << line << std::endl;
      continue;
    }
    //    std::cout << linenum << ": (" << x << "," << y << "," << z << ")" << std::endl;
    
    position.SetXYZ(x,y,z);
    bfield.SetXYZ(bx,by,bz);

    r = position.Perp();
    phi = position.Phi();
    
    br = bfield.Perp();
    bphi = bfield.Phi();

    B.Fill(r,phi,z,br,bphi,bz);
    std::cout << r << "," << phi << "," << z << "," << br << "," << bphi << "," << bz << std::endl; 

    linenum++; 
  }
  
  f->Write();

  return linenum;
}
