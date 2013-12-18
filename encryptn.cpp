#include <gmpxx.h>
#include <iostream>
#include <gmp.h>
#include <fstream>
#include <string>
#include <sstream>
#include "ecurve.hpp"
#include "point.hpp"

using namespace std;
#define L 23

void encrypt(string keyPub,string plaintext, string ciphertext,mpz_class seed) {
    ifstream keyFile(keyPub.c_str());
    if (!keyFile.is_open()) {
      cout<<"***********Open key Failure*********"<<endl;
      return;
    }
    string buffer;
    string token;
    mpz_class para[10];
    int i=0;
    
    while (!keyFile.eof()) {
      getline(keyFile,buffer);
      stringstream iss;
      iss<<buffer;
      while (getline(iss, token,' ')) {
	para[i].set_str(token,10);
	cout<<para[i]<<" ";
	i++;
      }
      cout<<'\n'<<i<<endl;
    }
    keyFile.close();
    ECurve ecurve(para[0],para[1],para[2],para[3],para[4],para[5]);
    
    
    mpz_class p = ecurve.getP();
    mpz_class n = ecurve.getN();
    mpz_class a = ecurve.getA();
    mpz_class b = ecurve.getB();
    mpz_class gx = ecurve.getGx();
    mpz_class gy = ecurve.getGy();
    
    Point alpha(para[6],para[7]);
    Point beta(para[8],para[9]);
    
    ifstream ptFile(plaintext.c_str());
    if (!ptFile.is_open()) {
      cout<<"***********Open pt Failure*********"<<endl;
      return;
    }
    
    ofstream ctFile(ciphertext.c_str());
    if (!ctFile.is_open()) {
      cout<<"***********Open ct Failure*********"<<endl;
      return;
    }
    
    mpz_class message;
    Point Y1;
    Point gama;
    mpz_class Y2;
    gmp_randclass r1 (gmp_randinit_default);
    r1.seed(seed);
     while (!ptFile.eof()) {
      getline(ptFile,buffer);
      if (!ptFile.eof()) {
	message.set_str(buffer,10);
	cout<<buffer<<endl;
      //generate random number k
     
	mpz_class k = r1.get_z_range(p);
      
      //compute Y1 & Y2
	Y1.times(k,alpha,ecurve);
	gama.times(k,beta,ecurve);
	Y2 = ecurve.mod(gama.getX()*message);
      
	ctFile<<Y1.getX()<<" "<<Y1.getY()<<" "<<Y2<<endl;
      }
      
      
     }
     ptFile.close();
     ctFile.close();  

}




int main(int argc, char* argv[]) {
    
  if (argc==5 || argc == 4) {
    mpz_class seed = time(0);
    if (argc == 5) {
      seed.set_str(argv[4],10);
    }
   
      encrypt(argv[1],argv[2],argv[3],seed);
    
  }  
  else {
    cout<<"*******************Wrong Number of Arguments!********************\n"<<endl;
  }
		
}
