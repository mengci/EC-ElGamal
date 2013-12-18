#include <gmpxx.h>
#include <iostream>
#include <gmp.h>
#include <fstream>
#include <string>
#include <sstream>
#include "ecurve.hpp"
#include "point.hpp"

using namespace std;

void decrypt(string keyPrv,string ciphertext, string plaintext) {
    
  //get out private key parameters
    ifstream keyFile(keyPrv.c_str());
    if (!keyFile.is_open()) {
      cout<<"***********Open key Failure*********"<<endl;
      return;
    }
    string buffer;
    string token;
    mpz_class para[11];
    int i=0;
    
//read the key parameters into array para[]
    while (!keyFile.eof()) {
      getline(keyFile,buffer);
      stringstream iss;
      iss<<buffer;
      while (getline(iss, token,' ')) {
	para[i].set_str(token,10);
	i++;
      }
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
    
    mpz_class secreta = para[10];
    
    // open file dat.ct & file dat_decrypted.pt
    ofstream ptFile(plaintext.c_str());
    if (!ptFile.is_open()) {
      cout<<"***********Open pt Failure*********"<<endl;
      return;
    }
    
    ifstream ctFile(ciphertext.c_str());
    if (!ctFile.is_open()) {
      cout<<"***********Open ct Failure*********"<<endl;
      return;
    }
    
    mpz_class message;
    Point Y1;
    Point gama;
    mpz_class gamaxInv;
    mpz_class Y1_x;
    mpz_class Y1_y;
    mpz_class Y2;
    
    
    // decrypt ciphertexts
     while (!ctFile.eof()) {
      getline(ctFile,buffer);
      if (!ctFile.eof()) {
	stringstream iss;
	iss<<buffer;
	
	//get Y1 & Y2
	getline(iss, token,' ');
	Y1_x.set_str(token,10);
	getline(iss, token,' ');
	Y1_y.set_str(token,10);
	getline(iss, token,' ');
	Y2.set_str(token,10); 
       
	Y1 = Point(Y1_x,Y1_y);
	
      //write decrypted message into dat-num-decrypted.pt
	gama.times(secreta,Y1,ecurve);
	gamaxInv = ecurve.modinv(gama.getX());
	
	message = ecurve.mod(Y2*gamaxInv);
	
	ptFile<<message<<endl;
	
      }
      
      
     }
     ptFile.close();
     ctFile.close();

}


int main(int argc, char* argv[]) {
    
  if (argc == 4) {
    decrypt(argv[1],argv[2],argv[3]);
  }  
  else {
    cout<<"*******************Wrong Number of Arguments!********************\n"<<endl;
  }
		
}
