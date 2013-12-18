#include <gmpxx.h>
#include <iostream>
#include <gmp.h>
#include <fstream>
#include <string>
#include <sstream>
#include "ecurve.hpp"
#include "point.hpp"
#define L 23
using namespace std;


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
	//cout<<para[i]<<" ";
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
    mpz_class k;
    gmp_randclass r1 (gmp_randinit_default);
    
    r1.seed(seed);
    
    // read in the plaintext file by fixed length L 
    ptFile.seekg(0,ptFile.end);
    int length = ptFile.tellg();
    ptFile.seekg(0,ptFile.beg);
      
      //read the file into the buffer
    char* ptext = new char[length];
    ptFile.read(ptext,length);
    ptFile.close();
      //read&print  data blocks
      
    mpz_class msg;
    //encrypt each block
    for (i=0;i<length;i++) {
      msg += ptext[i];
      msg=msg<<8;
      if ((i+1)%L == 0 || (i+1)==length) {
	cout<<msg<<endl;
	k = r1.get_z_range(p);
	Y1.times(k,alpha,ecurve);
	gama.times(k,beta,ecurve);
	Y2 = ecurve.mod(gama.getX()*msg);
	
	ctFile<<Y1.getX()<<" "<<Y1.getY()<<" "<<Y2<<endl;
	msg = 0;
     }
     
    }
    
    
    delete[] ptext;
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
