#include <gmpxx.h>
#include <iostream>
#include <gmp.h>
#include <fstream>
#include <string>
#include "ecurve.hpp"
#include "point.hpp"

using namespace std;

void genkey(string ecPara,string filename,mpz_class seed) {
    ifstream ecFile(ecPara.c_str());
    ECurve ecurve(ecFile);
    
    mpz_class p = ecurve.getP();
    mpz_class n = ecurve.getN();
    mpz_class a = ecurve.getA();
    mpz_class b = ecurve.getB();
    mpz_class gx = ecurve.getGx();
    mpz_class gy = ecurve.getGy();
    


    gmp_randclass r1 (gmp_randinit_default);
    r1.seed(seed);
    mpz_class secret = r1.get_z_range(p);

// alpha
    Point pt(gx,gy);

//  generate beta
    pt.times(secret,pt,ecurve);
    

    string filePub = filename;
    string filePrv = filename;
    filePub.append(".pub");
    filePrv.append(".prv");
// write the 10s parameters into pubKey file
    ofstream file1(filePub.c_str());
    if (file1.is_open()) {
      file1<<p<<"\n"<<n<<"\n"<<a<<"\n"<<b<<"\n"<<gx<<"\n"<<gy<<endl;
      file1<<gx<<" "<<gy<<"\n"<<pt.getX()<<" "<<pt.getY()<<endl;

    }
    file1.close();

// write the 11 parameters into prvKey file    
    ofstream file2(filePrv.c_str());
    if (file2.is_open()) {
      file2<<p<<"\n"<<n<<"\n"<<a<<"\n"<<b<<"\n"<<gx<<"\n"<<gy<<endl;
      file2<<gx<<" "<<gy<<"\n"<<pt.getX()<<" "<<pt.getY()<<endl;
      file2<<secret<<endl;
    }
    file2.close();
}


int main(int argc, char* argv[]) {
    
  if (argc==4 || argc == 3) {
    mpz_class seed = time(0);
    if (argc == 4) {
      seed.set_str(argv[3],10);
    }

    genkey(argv[1],argv[2],seed);
  }  
  else {
    cout<<"*******************Wrong Number of Arguments!********************\n"<<endl;
  }
		
}
