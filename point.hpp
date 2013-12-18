/*
 * ECPoint.hpp
 *
 *  Created on: Apr 20, 2012
 *      Author: mike
 */

#pragma once

#include "ecurve.hpp"

class Point {
private:
    mpz_class x;
    mpz_class y;

public:
    static const Point zero;

public:
    // Constructors
    Point() :
        x(-1), y(-1) {
    }
    template<typename T>
    Point(T x, T y) : x(x), y(y) {}

    // Get functions
    const mpz_class& getX() const {return x;}
    const mpz_class& getY() const {return y;}

    // Predicates
    bool isZero() const {return x == -1;}
    bool onCurve(ECurve& ec) const;

    // Arithmetic on points
    void add(Point Q, const ECurve& ec);
    void negate(const ECurve& ec);
    void sub(Point Q, const ECurve& ec);
    void times(mpz_class k, Point P, const ECurve& ec);

    // Stream I/O functions
    ostream& print(ostream& out) const;
    ostream& write(ostream& out) const;
    istream& read(istream& in);
};

inline ostream& operator<<(ostream& out, const Point& P) {
    return P.print(out);
}

