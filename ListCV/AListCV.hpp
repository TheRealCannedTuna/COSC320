// File: ListCV/AListCV.hpp

#ifndef AListCV_hpp
#define AListCV_hpp

#include <iostream> // ostream.
using namespace std;

template<class T> class AListCVVis; // Forward declaration of visitor class.

template<class T>
class AListCV: public enable_shared_from_this<AListCV<T>>  {
public:
    virtual ~AListCV() = default;
    virtual void accept(AListCVVis<T> &visitor) const = 0;
};

template<class T>
class AListCVVis {
public:
    virtual ~AListCVVis() = default;

    virtual void visitMTList(AListCV<T> const &host) = 0;
    virtual void visitNEList(AListCV<T> const &host) = 0;
};

template<class T>
ostream &operator<< (ostream &os, AListCV<T> const &rhs);
// Output a list to an ostream. See LCVtoStream.

#endif
