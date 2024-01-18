//
// Created by Dung Nguyen on 8/3/21.
//

#ifndef DP4DSDISTRIBUTION_ALISTCVZVIS_HPP
#define DP4DSDISTRIBUTION_ALISTCVZVIS_HPP

template<class T>
class AListCVZVis {
public:
    virtual ~AListCVZVis() = default;

    virtual shared_ptr<void> visitMTList(AListCVZ<T> const &host) = 0;
    virtual shared_ptr<void> visitNEList(AListCVZ<T> const &host) = 0;
};

#endif //DP4DSDISTRIBUTION_ALISTCVZVIS_HPP
