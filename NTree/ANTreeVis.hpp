// File: NTree/ANTreeVis.hpp

#ifndef ANTreeVIS_HPP_
#define ANTreeVIS_HPP_

template<class T>
class NTree; // Forward declaration.

// ========= ANTreeVis =========
template<class T>
class ANTreeVis {
public:
    virtual ~ANTreeVis() = default;

    virtual void caseAt(int size, NTree<T> &host) = 0;
    virtual void caseAt(int size, NTree<T> const &host) = 0;

};

#endif
