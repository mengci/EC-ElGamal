/*
 * eclib.hpp
 *
 *  Created on: Apr 20, 2012
 *      Author: mike
 */

#pragma once

#include <gmpxx.h>
#include <iostream>
#include <fstream>
using namespace std;

class ECurve {
private:
    mpz_class p;    // The prime modulus
    mpz_class n;    // The order of the group
    mpz_class a;    // Elliptic curve coefficient a
    mpz_class b;    // Elliptic curve coefficient b
    mpz_class Gx;   // Base point x coordinate
    mpz_class Gy;   // Base point y coordinate

public:
    ECurve() {
    }
    ECurve(const mpz_class& p, const mpz_class& n, const mpz_class& a,
            const mpz_class& b, const mpz_class& Gx, const mpz_class& Gy) :
            p(p), n(n), a(a), b(b), Gx(Gx), Gy(Gy) {
    }

    ECurve(ifstream& in) {
        in >> p >> n >> a >> b >> Gx >> Gy;
    }

    // Get functions
    const mpz_class& getP() const {return p;}
    const mpz_class& getN() const {return n;}
    const mpz_class& getA() const {return a;}
    const mpz_class& getB() const {return b;}
    const mpz_class& getGx() const {return Gx;}
    const mpz_class& getGy() const {return Gy;}

    // Predicates
    bool nonSing() const;

    // Number-theoretic functions
    mpz_class mod(const mpz_class a) const;
    mpz_class modexp(const mpz_class a, const mpz_class exp) const;
    mpz_class modinv(const mpz_class x) const;
    bool modsqrt(mpz_class& b, const mpz_class a) const;

    // Stream I/O functions
    ostream& print(ostream& out) const;
    ostream& write(ostream& out) const;
    istream& read(istream& in);
};

inline ostream& operator<<(ostream& out, const ECurve& ec) {
    return ec.print(out);
}
