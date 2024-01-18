// File: Polynomial/PolynomialMain.cpp

#include <cstdlib>  // EXIT_SUCCESS.
#include <fstream>  // ifstream.
#include "PolynomialC.hpp"
using namespace std;

int main() {
    PolynomialC poly0;                            //zero polynomial poly0 = 0
    PolynomialC poly1(Rational(7,9));           //constant polynomial poly1 = 7/9
    PolynomialC poly2(Rational(-3,5), 2);       //monomial poly2 = -3/5 x^2
    PolynomialC poly3(Rational(5,6), 8, poly2); //poly3 = 5/6 x^8 + -3/5 x^2
 
    cout << "The zero polynomial:  poly0 = 0.\n" << poly0 << endl;
    cout << "A constant polynomial:  poly1 = 7/9\n" << poly1 << endl;
    cout << "A monomial:  poly2 = -3/5 x^2:\n" << poly2 << endl;
    cout << "A multi-nomial:  poly3 = 5/6x^8 + -3/5x^2:\n" << poly3 << endl;
    cout << "Testing operator+:  poly3 + 1 + poly2:\n" <<(poly3 + Rational(1) + poly2) << endl;
    cout << "Testing operator=...\npoly2 before assignment:\n" << poly2 << endl;
    poly2 = poly2 + poly1 + poly3;
    cout << "poly2 after assignment poly2 = poly2 + poly1 + poly3:\n" << poly2 << endl;

    cout << "Testing operator<<\n..." << endl;
    ofstream outFile("poly.dat");
    outFile << poly2;
    outFile.close();

    cout << "Testing operator >>\n..." << endl;
    ifstream inFile("poly.dat");
    inFile >> poly0 ;
    cout << "poly0:\n" << poly0 << endl;
    inFile.close();
    inFile.open("constpoly.dat");
    inFile >> poly3;
    cout << "poly3:\n" << poly3 << endl;

    cout << "poly3(1) = " << poly3(1) <<endl;
    cout << "poly2(-1) = " << poly2(-1) <<endl;
 
    /*
      cout << "Testing assertion(which shoud fail!)..." << endl;
      Polynomial p(5, 0, Polynomial(6));
      cout << p;
    */
    return EXIT_SUCCESS;
}
