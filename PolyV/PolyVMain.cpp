/* 
 * File:   PolyVMain.cpp
 * Author: dxnguyen
 *
 * Created on January 22, 2013, 10:32 PM
 */

#include <iostream>
#include <cstdlib> // EXIT_SUCCESS.
#include <cctype> // toupper.
#include "Utilities.hpp" // promptIntBetween.
#include "PolyCV.hpp"
#include "PVwriteStreamVis.hpp"
#include "PVmulConstVis.hpp"
#include "PVmulVis.hpp"

using namespace std;

/*
 * 
 */
int main() {

// Making polynomials:
    APolyV *cp0 = new ConstPolyCV();  // = 0
    APolyV *cp1 = new ConstPolyCV(1); // = 1
    APolyV *cp2 = new ConstPolyCV(3); // = 3
    APolyV *ncp0 = new NonConstPolyCV(99, 3, *cp0); // = 99x^3
    APolyV *ncp1 = new NonConstPolyCV(66, 4, *cp1); // = 66x^4 + 1
    APolyV *ncp2 = new NonConstPolyCV(22, 5, *ncp0); // = 22x^5 + 99x^3
    APolyV *ncp3 = new NonConstPolyCV(33, 6, *ncp1); // = 33x^6 + 66x^4 + 1
    APolyV *ncp4_0 = new ConstPolyCV(-1); // = -1
    APolyV *ncp4_1 = new NonConstPolyCV(3, 1, *ncp4_0); // = 3x - 1
    APolyV *ncp4_2 = new NonConstPolyCV(2, 2, *ncp4_1); // = 2x^2 + 3x - 1
    APolyV *ncp4_3 = new NonConstPolyCV(3, 2, *ncp4_1); // = 3x^2 + 3x - 1
    APolyV *ncp4_4 = new NonConstPolyCV(-66, 4, *ncp4_2); // = -66x^4 + 2x^3 + 3x - 1
    APolyV *ncp4_5 = new NonConstPolyCV(1, 5, *ncp4_4); // = x^5 - 66x^4 + 2x^3 + 3x - 1
    APolyV *ncp4 = new NonConstPolyCV(-33, 6, *ncp4_5); // = -33x^6 + x^5 - 66x^4 + 2x^3 + 3x - 1
    APolyV *p1 = new NonConstPolyCV(1, 1, *cp0); // = x
    APolyV *p2 = new NonConstPolyCV(-1, 1, *cp0); // = -x

// Testing stream output:

    PVwriteStreamVis ws(cout);
    cout << "ncp1 = ";
    ncp1->accept(ws);
    cout << "\nncp2 = ";
    ncp2->accept(ws);
    cout << endl << "ncp3 = ";
    ncp3->accept(ws);
    cout << endl;
// Testing operator<<:
    cout << "ncp4 = " << *ncp4 << endl;
    cout << "p1 = " << *p1 << endl;
    cout << "p2 = " << *p2 << endl;

// Testing operator():
    cout <<"\nTesting polynomial evaluation, operator()" << endl;
    cout << "ncp1(1) = " << (*ncp1)(1) << endl;
    cout << "ncp3(2) = " << (*ncp3)(2) << endl;
    cout << "ncp4(-1) = " << (*ncp4)(-1) << endl;
    
// Testing operator+:
    cout <<"\nTesting addition (operator +)" << endl;
    APolyV* ncp5 = *cp0 + *cp1;
    cout << "cp0 + cp1 = " << *ncp5 << endl;
    APolyV* ncp5_1 = *cp1 + *cp0;
    cout << "cp1 + cp0 = " << *ncp5_1 << endl;

    APolyV* ncp6 = *ncp1 + *ncp0;
    cout << "\nncp1 + ncp0 = " << *ncp6 << endl;
    APolyV* ncp6_1 = *ncp0 + *ncp1;
    cout << "ncp0 + ncp1 = " << *ncp6_1 << endl;
    
    APolyV* ncp7 = *ncp2 + *ncp4;
    cout << "\nncp2 + ncp4 = " << *ncp7 << endl;
    APolyV* ncp7_1 = *ncp4 + *ncp2;
    cout << "ncp4 + ncp2 = " << *ncp7_1 << endl;
    
    APolyV* ncp8 = *ncp3 + *ncp4;
    cout << "\nncp3 + ncp4 = " << *ncp8 << endl;
    APolyV* ncp8_1 = *ncp4 + *ncp3;
    cout << "ncp4 + ncp3 = " << *ncp8_1 << endl;

    APolyV *ncp9 = *ncp2 + *p1;
    cout << "\nncp2 + p1 = " << *ncp9 << endl;
    APolyV *ncp9_1 = *p1 + *ncp2;
    cout << "p1 + ncp2 = " << *ncp9_1 << endl;
    
    APolyV *ncp10 = *ncp1 + *p2 ;
    cout << "\nncp1 + p2 = "  << *ncp10 << endl;
    APolyV *ncp10_1 = *p2 + *ncp1;
    cout << "p2 + ncp1 = "  << *ncp10_1 << endl;
    
// Test multiplication by a Rational:
    cout <<"\nTesting multiplication by a Rational constant" << endl;
    PVmulConstVis mcv(3);
    ncp4->accept(mcv);
    APolyV* m1 = mcv.result();
    cout << "3 * ncp4 = " << *m1 << endl;
    delete m1;
    mcv.setMultiplier(0); 
    ncp4->accept(mcv);
    m1 = mcv.result();
    cout << "0 * ncp4 = " << *m1 << endl;
    delete m1;
    m1 = 2 * (*ncp4);  // 2 is implicitly converted to Rational(2) here.
    cout << "2 * ncp4 = " << *m1 << endl;
    delete m1;
    
// Test subtraction:
    cout <<"\nTesting subtraction" << endl;
    APolyV *d1 = *ncp2 - *ncp0;
    cout << "cp2 - ncp0 = " << *d1 << endl;
    APolyV *d2 = *ncp3 - *ncp4;
    cout << "ncp3 - ncp4 = " << *d2 << endl;
    APolyV *d3 = *ncp2 - *ncp7;
    cout << "ncp2 - (ncp2 + ncp4) = " << *d3 << endl;
    
// Test unary minus:
    cout <<"\nTesting unary minus" << endl;
    APolyV *mcp0 = -(*cp0);
    cout << "-cp0 = " << *mcp0 << endl;
    APolyV *mcp1 = -*cp1;
    cout << "-cp1 = " << *mcp1 << endl;
    APolyV *mncp4 = -*ncp4;
    cout << "-ncp4 = " << *mncp4 << endl;
    
// Test multiplication
    cout <<"\nTesting multiplication (operator*)" << endl;
    APolyV *m0 = (*cp0) * (*ncp0);
    cout <<  *cp0 << " * " << *ncp0 << " = " << *m0 << endl;
    delete m0;
    m0 = (*ncp1) * (*ncp4_2);
    cout << "(" << *ncp1 << ") * (" << (*ncp4_2) << ") = " << *m0 << endl;
    
// Test long division:
    cout <<"\nTesting long division (operator/ and operator%)" << endl;
    APolyV *q = *ncp3 / *cp2;
    cout <<  *ncp3 << " / " << *cp2 << " = " << *q << endl;
    APolyV *r = *ncp3 % *cp2;
    cout <<  *ncp3 << " % " << *cp2 << " = " << *r << endl;
    APolyV *s = *((*cp2) * (*q)) + *r;
    cout <<  "(" << *cp2 << ") * (" << *q << ") + (" << *r << ") = " << *s << "\n" << endl;    
    delete q;
    delete r;
    delete s;
   
    q = *ncp1 / *ncp2;
    cout <<  *ncp1 << " / " << *ncp2 << " = " << *q << endl;
    r = *ncp1 % *ncp2;
    cout <<  *ncp1 << " % " << *ncp2 << " = " << *r << endl;
    s = *((*ncp2) * (*q)) + *r;
    cout <<  "(" << *ncp2 << ") * (" << *q << ") + (" << *r << ") = " << *s << "\n" << endl;    
    delete q;
    delete r;
    delete s;

    q = *ncp4_3 / *ncp4_2;
    cout <<  *ncp4_3 << " / " << *ncp4_2 << " = " << *q << endl;
    r = *ncp4_3 % *ncp4_2;
    cout <<  *ncp4_3 << " % " << *ncp4_2 << " = " << *r << endl;
    s = *((*ncp4_2) * (*q)) + *r;
    cout <<  "(" << *ncp4_2 << ") * (" << *q << ") + (" << *r << ") = " << *s << "\n" << endl;    
    delete q;
    delete r;
    delete s;

    q = *ncp4 / *ncp4_2;
    cout <<  *ncp4 << " / " << *ncp4_2 << " = " << *q << endl;
    r = *ncp4 % *ncp4_2;
    cout <<  *ncp4 << " % " << *ncp4_2 << " = " << *r << endl;
    s = *((*ncp4_2) * (*q)) + *r;
    cout <<  "(" << *ncp4_2 << ") * (" << *q << ") + (" << *r << ") = " << *s << "\n" << endl;    
    delete q;
    delete r;
    delete s;
      
    cout << "\nDone!" << endl;
    
    delete cp0;
    delete cp1;
    delete ncp0;
    delete ncp1;
    // ...
    delete ncp10;
    // need to delete all pointers.

    return EXIT_SUCCESS;
}

