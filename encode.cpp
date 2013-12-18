#include <gmpxx.h>
#include <iostream>
#include <gmp.h>
#include <fstream>
#include <string>
#include "ecurve.hpp"
#include "point.hpp"

using namespace std;

void encode(string ecPara,string data) {
    ifstream ecFile(ecPara.c_str());
    ECurve ecurve(ecFile);
    
    mpz_class p = ecurve.getP();
    mpz_class n = ecurve.getN();
    mpz_class a = ecurve.getA();
    mpz_class b = ecurve.getB();
    mpz_class gx = ecurve.getGx();
    mpz_class gy = ecurve.getGy();
    
    
    cout << "p: " << p << endl;
    cout << "n: " << n << endl;
    cout << "a: " << a << endl;
    cout << "b: " << b << endl;
    cout << "gx: " << gx << endl;
    cout << "gy: " << gy << endl;
    cout<<endl;
    
    cout<<"The curve is non-singular? ";
    if (ecurve.nonSing())
      cout<<"Yes"<<endl;
    else
      cout<<"No"<<endl;
    
    
    Point pt(gx,gy);
    cout<<"Basepoint(gx,gy) lies on the curve?";
    if (pt.onCurve(ecurve))
      cout<<"Yes"<<endl;
    else
      cout<<"No"<<endl;
    
    
//     print out the data file as l-sized blocks
    int l=0;
    mpz_class product = 1;
    while (product < p) {
      product = product * 256;
      l++;
    } 
    l--;
    cout<<endl;
    cout<<"The largest integer l: "<<l<<endl;
    cout<<endl;
    
    ifstream dataFile(data.c_str());
    
    if (dataFile.is_open()) {
      //get the length of file
      dataFile.seekg(0,dataFile.end);
      int length = dataFile.tellg();
      dataFile.seekg(0,dataFile.beg);
      
      //read the file into the buffer
      char * buffer = new char[length];
      dataFile.read(buffer,length);
      dataFile.close();
      //read&print  data blocks
      
      int i;
      for (i=0;i<length;i++) {
	  cout<<buffer[i];
	  if ((i+1)%l == 0) {
	    cout<<endl;
	  }
      }
      
      delete[] buffer;
      
    }
    
}

int main(int argc, char* argv[]) {
    
  if (argc==3) {
    encode(argv[1],argv[2]);
  }  
  else {
    cout<<"*******************Wrong Number of Arguments!********************\n"<<endl;
  }
		
}
