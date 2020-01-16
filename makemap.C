#include <iostream>
#include <fstream>
#include <sstream>

#include "TFile.h"
#include "TNtuple.h"

Int_t makemap( std::string filename = "TPC_fld_map_f_shiftby2p85cm.table" )
{
  std::ifstream ifs( filename ); 
  std::string line; 

  double x,y,z;
  double bx,by,bz;
  
  double rho,phi;
  double brho,bphi;

  // unit vector from the origin to (x,y) 
  double vx,vy;

  std::string rootfile = "sphenix3dmaprhophiz.root";
  TFile *f = new TFile(rootfile.c_str(),"recreate");
  TNtuple B("B","sPHENIX 3D Field Map TPC_fld_map_f_shiftby2p85cm 2020.01.16 (Gauss)","rho:phi:z:brho:bphi:bz");
  
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
    
    rho = sqrt(x*x + y*y);
    phi  = atan2(y,x);
    
    vx = x/rho;
    vy = y/rho;

    brho = bx*vx + by*vy;
    bphi = -by*vx + bx*vy;

    B.Fill(rho,phi,z,brho,bphi,bz);
    std::cout << rho << "," << phi << "," << z << "," << brho << "," << bphi << "," << bz << std::endl; 

    linenum++; 
  }
  
  f->Write();

  return linenum;
}
