//
// Created by Dung Nguyen on 8/3/21.
//

#ifndef DP4DSDISTRIBUTION_ALISTCVZ_HPP
#define DP4DSDISTRIBUTION_ALISTCVZ_HPP

#include <iostream> // ostream.
using namespace std;

template<class T> class AListCVZVis; // Forward declaration.

template<class T>
class AListCVZ: public enable_shared_from_this<AListCVZ<T>>  {
public:
    virtual ~AListCVZ() = default;

    virtual T const &first() const = 0 ;
    virtual shared_ptr<const AListCVZ<T>> rest() const = 0;
    virtual shared_ptr<void> accept(AListCVZVis<T> &visitor) const = 0;
};

template<class T>
ostream &operator<< (ostream &os, AListCVZ<T> const &rhs);
// Output a list to an ostream. See LCVtoStream.

#endif //DP4DSDISTRIBUTION_ALISTCVZ_HPP
